/*
 * Author: LiZhaojia 
 *
 * Last modified: 2014-09-22 19:19 +0800
 *
 * Description: 环形无锁队列， 单生产者 单消费者，效率考虑，长度为2的幂
 */

#ifndef WATER_BASE_LOCK_FREE_CIRCULAR_QUEUE_HPP
#define WATER_BASE_LOCK_FREE_CIRCULAR_QUEUE_HPP

#include <vector>
#include <atomic>

namespace water{

template <typename T>
class LockFreeCircularQueue
{
    struct Cell
    {
        enum class Status : uint_fast32_t 
        {
            empty, 
            full, 
        };

        Cell()
        : status(Status::empty), t()
        {
        }

        std::atomic<Status> status;
        T t;
    };

public:
    LockFreeCircularQueue(uint64_t powArg) //队列长度为 pow(2, powArg)
    : m_begin(0), m_end(0), m_pow(powArg), m_maxSize(1u < powArg), m_size(0), m_data(m_maxSize)
    {
    }

    ~LockFreeCircularQueue()
    {
    }

    bool push(const T& item)
    {
        const uint_fast32_t pos = realPos(m_end);
        while(int i = 1)
        {
            Cell::Status oldStatus = m_data[pos].status.load(std::memory_order_relaxed);
            if(oldStatus == Cell::Status::full && i++ == 5) //最多尝试5次数依然队列满，返回失败，无法放入;
                return false;
        }

        //队尾后移
        m_end++;

        //向节点填入数据
        m_data[oldEnd].t = item;

        //标记为已放入并将提交内存修改，令所有线程可见
        m_data[pos].status.store(Cell::Status::full, std::memory_order_release);
        return true;
    }

    bool pop(T* t)
    {
        const uint_fast32_t pos = realPos(m_begin);
        while(int i = 1)
        {
            Cell::Status oldStatus = m_data[pos].status.load(std::memory_order_relaxed);
            if(oldStatus == Cell::Status::empty && i++ == 5) //最多尝试5次数依然队列空，返回失败，无法取出;
                return false;
        }

        //队首后移
        m_begin++;

        //取出节点内的数据
        *t = m_data[oldBegin].t;

        //标记为已取出并将提交内存修改，令所有线程可见
        m_data[oldBegin].status.store(Cell::Status::empty,
                                      std::memory_order_release);
        return true;
    }

    bool empty() const
    {
        return m_data[m_begin].status.load(std::memory_order_relaxed) == Cell::Status::empty;
    }

    inline uint64_t maxSize() const
    {
        return static_cast<uint64_t>(m_data.size());
    }

private:
    inline uint64_t realPos(uint64_t pos) const
    {
        return m_size & (maxSize() - 1);
    }

private:
    uint_fast32_t m_begin;
    uint_fast32_t m_end;
    const uint_fast32_t m_maxSize;
    std::vector<Cell> m_data;
};

}

#endif //#ifndef WATER_BASE_CIRCULAR_QUEUE_HPP
