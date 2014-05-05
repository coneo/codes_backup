#ifndef WATER_TOOLS_SERIALIZE_STREAM_H
#define WATER_TOOLS_SERIALIZE_STREAM_H

#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <forward_list>


class SerializeStream
{
    typedef std::basic_string<uint8_t> Buffer;
public:

    typedef Buffer::size_type size_type;

    SerializeStream() = default;
    ~SerializeStream() = default;

    inline size_type tellg() const
    {
        return ipos;
    }

    inline size_type tellp() const
    {
        return opos;
    }

    inline void reset()
    {
        buffer.clear();
        ipos = 0;
        opos = 0;
    }


    //pod type
    template <typename T>
    inline SerializeStream& operator << (const T& t)
    {
        buffer.append((const uint8_t*)&t, sizeof(t));
        opos += sizeof(t);

        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (T& t)
    {
        uint8_t* p = (uint8_t*)&t;
        for(size_type i = 0; i < sizeof(t) && ipos < buffer.size(); ++i)
        {
            *(p + i) = buffer.at(ipos);
            ++ipos;
        }
            
        return *this;
    }

    //std::string
    inline SerializeStream& operator << (const std::string& str)
    {
        (*this) << str.size();

        buffer.append((const uint8_t*)str.data(), str.size());
        opos += str.size();

        return *this;
    }

    inline SerializeStream& operator >> (std::string& str)
    {
        std::string::size_type size = 0;
        (*this) >> size;
        
        str.assign((const char*)(buffer.data() + ipos), size);
        ipos += size;

        return *this;
    }

    //std::pair
    template <typename T1, typename T2>
    inline SerializeStream& operator << (const std::pair<T1, T2>& pair)
    {
        (*this) << pair.first;
        (*this) << pair.second;

        return *this;
    }

    template <typename T1, typename T2>
    inline SerializeStream& operator >> (std::pair<T1, T2>& pair)
    {
        (*this) >> pair.first;
        (*this) >> pair.second;

        return *this;
    }

    //std::vector
    template <typename T>
    inline SerializeStream& operator << (const std::vector<T>& vec)
    {
        serializeContainer(vec);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::vector<T>& vec)
    {
        deserializeRandomAccessContainer(vec);
        return *this;
    }

    //std::basic_string
    template <typename T>
    inline SerializeStream& operator << (const std::basic_string<T>& vec)
    {
        serializeContainer(vec);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::basic_string<T>& vec)
    {
        deserializeRandomAccessContainer(vec);
        return *this;
    }

    //std::set
    template <typename T>
    inline SerializeStream& operator << (const std::set<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::set<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::multiset
    template <typename T>
    inline SerializeStream& operator << (const std::multiset<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::multiset<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::unordered_set
    template <typename T>
    inline SerializeStream& operator << (const std::unordered_set<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::unordered_set<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::unordered_multiset
    template <typename T>
    inline SerializeStream& operator << (const std::unordered_multiset<T>& s)
    {
        serializeContainer(s);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::unordered_multiset<T>& s)
    {
        deserializeContainer(s);
        return *this;
    }

    //std::map
    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator << (const std::map<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator >> (std::map<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::multimap
    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator << (const std::multimap<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator >> (std::multimap<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::unordered_map
    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator << (const std::unordered_map<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator >> (std::unordered_map<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::unordered_multimap
    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator << (const std::unordered_multimap<KeyT, ValueT>& m)
    {
        serializeContainer(m);
        return *this;
    }

    template <typename KeyT, typename ValueT>
    inline SerializeStream& operator >> (std::unordered_multimap<KeyT, ValueT>& m)
    {
        deserializeContainer(m);
        return *this;
    }

    //std::list
    template <typename T>
    inline SerializeStream& operator << (const std::list<T>& l)
    {
        serializeContainer(l);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::list<T>& l)
    {
        deserializeContainer(l);
        return *this;
    }

    //std::forward_list
    template <typename T>
    inline SerializeStream& operator << (const std::forward_list<T>& l)
    {
        serializeContainer(l);
        return *this;
    }

    template <typename T>
    inline SerializeStream& operator >> (std::forward_list<T>& l)
    {
        typedef typename std::forward_list<T> ContainerT;

        typename ContainerT::size_type size = 0;
        (*this) >> size;

        ContainerT::value_type tmp;
        container.push_front(std::move(tmp));
        ContainerT::iterator iter = l.begin();
        for(typename ContainerT::size_type i = 0; i < size; ++i)
        {
            typename ContainerT::value_type t;
            (*this) >> t;
            iter = l.insert_after(iter, std::move(t));
        }
        container->pop_front();

        return *this;
    }

private:
    template <typename T>
    inline SerializeStream& operator << (const T&);
    template <typename T>
    inline SerializeStream& operator >> (T&);

private:
    //serialize container
    template <typename ContainerT>
    inline void serializeContainer(const ContainerT& container)
    {
        typename ContainerT::size_type size = container.size();
        (*this) << size;

        for(const typename ContainerT::value_type& item : container)
            (*this) << item;
    }

    //deserialize container
    template <typename ContainerT>
    inline void deserializeContainer(ContainerT& container)
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
    inline void deserializeRandomAccessContainer(RandomAccessContainerT& container)
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
