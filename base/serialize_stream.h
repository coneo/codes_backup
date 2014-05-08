#ifndef WATER_TOOLS_SERIALIZE_STREAM_H
#define WATER_TOOLS_SERIALIZE_STREAM_H

#include <type_traits>
#include <cstring>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <forward_list>


#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

class RawMemoryBuffer
{
public:
    typedef uint32_t size_type;
    typedef uint8_t value_type;
/*
    explicit RawMemoryBuffer(value_type* buf, size_type bufSize)
    :m_rawBuffer(buf), m_bufSize(bufSize)
    {
    }
*/
    RawMemoryBuffer() = default;
    ~RawMemoryBuffer() = default;

    RawMemoryBuffer(const RawMemoryBuffer&) = delete;
    RawMemoryBuffer& operator=(const RawMemoryBuffer&) = delete;

    RawMemoryBuffer(RawMemoryBuffer&& other)
    {
        
        m_bufSize = other.m_bufSize;
        m_rawBuffer= other.m_rawBuffer;

        other.clear();
    }

    inline size_type size() const
    {
        return m_size;
    }

    inline void clear()
    {
        m_size = 0;
        m_bufSize = 0;
    }

    inline value_type* data() const
    {
        return m_rawBuffer;
    }

    inline value_type at(size_type pos) const
    {
        return m_rawBuffer[pos];
    }

    inline value_type& at(size_type pos)
    {
        return m_rawBuffer[pos];
    }

    inline void assign(value_type* buf, size_type bufSize)
    {
        m_rawBuffer = buf;
        m_bufSize = bufSize;
        m_size = 0;
    }

    inline void swap(RawMemoryBuffer& other)
    {
        size_type tempS = m_bufSize;
        m_bufSize = other.m_bufSize;
        other.m_bufSize = tempS;

        value_type* tempB = m_rawBuffer;
        m_rawBuffer = other.m_rawBuffer;
        other.m_rawBuffer = tempB;
    }

    inline size_type copy(value_type* buf, size_type len, size_type pos = 0) const
    {
        if(m_size < pos)
            return 0;

        size_type ret = m_size - pos < len ? m_size - pos : len;
        ::memcpy(buf, m_rawBuffer + pos, ret);
        return ret;
    }

    inline size_type append(const value_type* buf, size_type len)
    {
        size_type ret = m_bufSize - m_size < len ? m_size - m_bufSize : len;
        ::memcpy(m_rawBuffer + m_size, buf, ret);
        m_size += ret;
        return ret;
    }

private:
    size_type m_size = 0;
    value_type* m_rawBuffer = nullptr;
    size_type m_bufSize = 0;
};


template<typename Buffer = std::basic_string<uint8_t>>
class SerializeStream
{
public:

    typedef typename Buffer::size_type size_type;

    SerializeStream() = default;
    ~SerializeStream() = default;

    SerializeStream(SerializeStream&& other)
    {
        clear();
        buffer.swap(other.buffer);
    }

    void assign(const void* buf, uint32_t bufSize)
    {
        typename Buffer::value_type* p = (typename Buffer::value_type*)buf;
        clear();
        buffer.assign(p, bufSize);
    }

    uint32_t copy(void* buf, uint32_t bufSize)
    {
        return buffer.copy(buf, bufSize);
    }

    size_type tellg() const
    {
        return ipos;
    }

    size_type tellp() const
    {
        return opos;
    }

    void clear()
    {
        buffer.clear();
        ipos = 0;
        opos = 0;
    }

    //std::string
    SerializeStream& operator << (const std::string& str)
    {
        (*this) << str.size();

        buffer.append((const typename Buffer::value_type*)str.data(), str.size());
        opos += str.size();

        return *this;
    }

    SerializeStream& operator >> (std::string& str)
    {
        std::string::size_type size = 0;
        (*this) >> size;
        
        str.assign((const char*)(buffer.data() + ipos), size);
        ipos += size;

        return *this;
    }

    //std::pair
    template <typename T1, typename T2>
    SerializeStream& operator << (const std::pair<T1, T2>& pair)
    {
        (*this) << pair.first;
        (*this) << pair.second;

        return *this;
    }

    template <typename T1, typename T2>
    SerializeStream& operator >> (std::pair<T1, T2>& pair)
    {
        (*this) >> pair.first;
        (*this) >> pair.second;

        return *this;
    }

    //std::vector
    template <typename T>
    SerializeStream& operator << (const std::vector<T>& vec)
    {
        serializeContainer(vec);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::vector<T>& vec)
    {
        deserializeRandomAccessContainer(vec);
        return *this;
    }

    //std::basic_string
    template <typename T>
    SerializeStream& operator << (const std::basic_string<T>& vec)
    {
        serializeContainer(vec);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::basic_string<T>& vec)
    {
        deserializeRandomAccessContainer(vec);
        return *this;
    }

    //std::set
    template <typename T>
    SerializeStream& operator << (const std::set<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::set<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::multiset
    template <typename T>
    SerializeStream& operator << (const std::multiset<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::multiset<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::unordered_set
    template <typename T>
    SerializeStream& operator << (const std::unordered_set<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::unordered_set<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::unordered_multiset
    template <typename T>
    SerializeStream& operator << (const std::unordered_multiset<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::unordered_multiset<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::map
    template <typename KeyT, typename ValueT>
    SerializeStream& operator << (const std::map<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    SerializeStream& operator >> (std::map<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::multimap
    template <typename KeyT, typename ValueT>
    SerializeStream& operator << (const std::multimap<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    SerializeStream& operator >> (std::multimap<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::unordered_map
    template <typename KeyT, typename ValueT>
    SerializeStream& operator << (const std::unordered_map<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    SerializeStream& operator >> (std::unordered_map<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::unordered_multimap
    template <typename KeyT, typename ValueT>
    SerializeStream& operator << (const std::unordered_multimap<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    SerializeStream& operator >> (std::unordered_multimap<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::list
    template <typename T>
    SerializeStream& operator << (const std::list<T>& l)
    {
        serializeContainer(l);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::list<T>& l)
    {
        deserializeContainer(l);
        return *this;
    }

    //std::forward_list
    template <typename T>
    SerializeStream& operator << (const std::forward_list<T>& container)
    {
        serializeContainer(container);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (std::forward_list<T>& container)
    {
        typedef typename std::forward_list<T> ContainerT;

        typename ContainerT::size_type size = 0;
        (*this) >> size;

        typename ContainerT::value_type tmp;
        container.push_front(std::move(tmp));
        typename ContainerT::iterator iter = container.begin();
        for(typename ContainerT::size_type i = 0; i < size; ++i)
        {
            typename ContainerT::value_type t;
            (*this) >> t;
            iter = container.insert_after(iter, std::move(t));
        }
        container->pop_front();

        return *this;
    }

    //type without corresponding operator << ; non trivial type whill occur a compile error
    template <typename T>
    SerializeStream& operator << (const T& t)
    {
        serialize(t, std::integral_constant<bool, std::is_trivial<T>::value>());//std::is_trivially_copyable<T>);
        return *this;
    }

    template <typename T>
    SerializeStream& operator >> (T& t)
    {
//#if GCC_VERSION > 
        deserialize(t, std::integral_constant<bool, std::is_trivial<T>::value>());//std::is_trivially_copyable<T>);
        return *this;
    }

private:
    //serialize trivial type
    template <typename TrivialType>
    void serialize(const TrivialType& t, std::true_type)
    {
        buffer.append((const typename Buffer::value_type*)&t, sizeof(t));
        opos += sizeof(t);
    }

    //serialize non - trivial type
    template <typename TrivialType>
    void serialize(const TrivialType&, std::false_type);

    //deserializeContainer trivial type
    template <typename TrivialType>
    void deserialize(const TrivialType& t, std::true_type)
    {
        typename Buffer::value_type* p = (typename Buffer::value_type*)&t;
        for(size_type i = 0; i < sizeof(t) && ipos < buffer.size(); ++i)
        {
            *(p + i) = buffer.at(ipos);
            ++ipos;
        }
    }

    //deserializeContainer non-trivial type
    template <typename TrivialType>
    void deserialize(const TrivialType&, std::false_type);

    //serialize container
    template <typename ContainerT>
    void serializeContainer(const ContainerT& container)
    {
        typename ContainerT::size_type size = container.size();
        (*this) << size;

        for(const typename ContainerT::value_type& item : container)
            (*this) << item;
    }

    //deserialize container
    template <typename ContainerT>
    void deserializeContainer(ContainerT& container)
    {
        container.clear();

        typename ContainerT::size_type size = 0;
        (*this) >> size;

        for(typename ContainerT::size_type i = 0; i < size; ++i)
        {
            typename ContainerT::value_type t;
            (*this) >> t;
            container.insert(container.end(), std::move(t));
        }
    }

    //deserialize random access container
    template <typename RandomAccessContainerT>
    void deserializeRandomAccessContainer(RandomAccessContainerT& container)
    {
        typename RandomAccessContainerT::size_type size = 0;
        (*this) >> size;

        container.resize(size);
        for(typename RandomAccessContainerT::size_type i = 0; i < size; ++i)
            (*this) >> container[i];
    }

private:
    Buffer buffer;
    size_type ipos = 0;
    size_type opos = 0;
};

#endif
