#ifndef WATER_BASE_CIRCULAR_QUEUE_HPP
#define WATER_BASE_CIRCULAR_QUEUE_HPP

#include "exception.h"

#include <vector>

namespace water{

DEFINE_EXCEPTION(GetFromEmptyCircularQueue, ExceptionBase)

template <typename T>
class CircularQueue
{
public:
    CircularQueue(uint32_t maxSize = 10)
    : m_data(maxSize)
    {
    }

    ~CircularQueue()
    {
    }

    T& get()
    {
        if(empty())
            EXCEPTION(GetFromEmptyCircularQueue, "")

        return m_data[m_begin];
    }

    bool push(T item)
    {
        if(size() == maxSize())
            return false;

        m_data[m_end] = item;
        m_end = nextPos(m_end);

        m_empty = false;
        return true;
    }

    void pop()
    {
        if(empty())
            return;

        m_begin = (m_begin + 1) % maxSize();

        if(m_begin == m_end)
            m_empty = true;
    }

    uint32_t maxSize() const
    {
        return static_cast<uint32_t>(m_data.size());
    }

    uint32_t size() const
    {
        if(empty())
            return 0;

        if(m_end == m_begin)
            return maxSize();

        return (m_end + maxSize() - m_begin) % maxSize();
    }

    bool empty() const
    {
        return m_empty;
    }

    void traverse(std::function<bool (T&)> callback)
    {
        const uint32_t itemSize = size();
        for(uint32_t i = m_begin, traversed = 0; traversed < itemSize; i = nextPos(i), ++traversed)
        {
            if(!callback(m_data[i]))
                break;
        }
    }

    void traverse(std::function<bool (const T& callback)> callback) const
    {
        const uint32_t itemSize = size();
        for(uint32_t i = m_begin, traversed = 0; traversed < itemSize; i = nextPos(i), ++traversed)
        {
            if(!callback(m_data[i]))
                break;
        }
    }

private:
    inline uint32_t nextPos(uint32_t pos) const
    {
        return (pos + 1) % maxSize();
    }
    

private:
    uint32_t m_begin = 0;
    uint32_t m_end = 0;
    bool m_empty = true;
    std::vector<T> m_data;
};

}

#endif //#ifndef WATER_BASE_CIRCULAR_QUEUE_HPP
