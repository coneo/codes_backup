#ifndef WATER_BASE_M_LOCK_FREE_CIRCULAR_QUEUE_HPP
#define WATER_BASE_M_LOCK_FREE_CIRCULAR_QUEUE_HPP

#include <vector>
#include <atomic>

namespace water{

template <typename T>
class MLockFreeCircularQueue
{
    struct Cell
    {
        enum class Status : uint_fast32_t 
        {
            empty, 
            full, 
        };

        Cell()
        : status(Status::empty) ,t()
        {
        }

        std::atomic<Status> status;
        T t;
    };

    struct Pos
    {
        enum class Operation : uint_fast32_t
        {
            writing,
            reading,
            none
        };

        Pos( Operation op = Operation::none, uint32_t i = 0)
        : operation(op), index(i)
        {
        }

        Operation operation;
        uint_fast32_t index;
    };

public:
    explicit MLockFreeCircularQueue(uint64_t powArg = 16)
    : m_begin(Pos(Pos::Operation::none, 0)), m_end(Pos(Pos::Operation::none, 0)), m_maxSize(1u << powArg), m_data(m_maxSize)
    {
    }

    ~MLockFreeCircularQueue() = default;

    bool isLockFree() const
    {
        return m_begin.is_lock_free();
    }

    bool push(const T& item)
    {
        Pos oldEnd = m_end.load(std::memory_order_relaxed);//队尾
        int i = 0;
        while(true) //尝试锁定队尾为可写
        {
            if(i++ == 5) //最大尝试次数
                return false;

            uint_fast32_t index = realIndex(oldEnd.index);

            oldEnd.operation = Pos::Operation::none;     //m_end的操作状态为none时cas才会成功
            Pos newEnd(Pos::Operation::writing, oldEnd.index);  //需用cas把m_end的操作状态改为writing

            if(!m_end.compare_exchange_weak(oldEnd, newEnd)) //cas失败则重试
                continue;

            if(m_data[index].status.load(std::memory_order_relaxed) == Cell::Status::full) //格子非空, 即队列满, 还原m_end, 并继续重试
            {
                m_end.store(Pos(Pos::Operation::none, oldEnd.index), std::memory_order_relaxed);
                continue;
            }

            //数据放入队列
            m_data[index].t = item;
            m_data[index].status.store(Cell::Status::full, std::memory_order_release);

            //队尾后移
            m_end.store(Pos(Pos::Operation::none, oldEnd.index + 1), std::memory_order_relaxed);
            break;
        }
        return true;
    }

    bool pop(T* t)
    {
        Pos oldBegin = m_begin.load(std::memory_order_relaxed);//队首
        int i = 1;
        while(true) //尝试锁定队首为可读
        {
            if(i++ == 5) //最大尝试次数
                return false;

            uint_fast32_t index = realIndex(oldBegin.index);

            oldBegin.operation = Pos::Operation::none;    //m_begin的操作状态为none时cas才会成功
            Pos newBegin(Pos::Operation::reading, oldBegin.index); //需用cas把m_begin的操作状态改为reading

            if(!m_begin.compare_exchange_weak(oldBegin, newBegin)) //cas失败则重试
                continue;

            if(m_data[index].status.load(std::memory_order_relaxed) == Cell::Status::empty) //格子为空, 即空队列, 还原m_begin, 并继续重试
            {
                m_end.store(Pos(Pos::Operation::none, oldBegin.index), std::memory_order_relaxed);
                continue;
            }

            //取出节点内的数据
            *t = m_data[index].t;
            m_data[index].status.store(Cell::Status::empty, std::memory_order_release);

            //队首后移
            m_begin.store(Pos(Pos::Operation::none, oldBegin.index + 1), std::memory_order_relaxed);
            break;
        }
        return true;
    }

    bool empty() const
    {
        return m_data[m_begin.load(std::memory_order_relaxed).index].status.load(std::memory_order_relaxed) == Cell::Status::empty;
    }

    bool full() const
    {
        return m_data[m_end.load(std::memory_order_relaxed).index].status.load(std::memory_order_relaxed) == Cell::Status::full;
    }

    inline uint64_t maxSize() const
    {
        return static_cast<uint64_t>(m_data.size());
    }

private:
    inline uint64_t realIndex(uint64_t index) const
    {
        return index & (maxSize() - 1);
    }

private:
    std::atomic<Pos> m_begin;
    std::atomic<Pos> m_end;
    const uint_fast32_t m_maxSize;
    std::vector<Cell> m_data;
};

}

#endif //#ifndef WATER_BASE_CIRCULAR_QUEUE_HPP
