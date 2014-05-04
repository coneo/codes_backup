#ifndef WATER_TOOLS_SERIALIZE_STREAM_H
#define WATER_TOOLS_SERIALIZE_STREAM_H

#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>



class SerializableStream
{
    typedef std::basic_string<uint8_t> Buffer;
public:

    typedef Buffer::size_type size_type;

    SerializableStream();
    ~SerializableStream();

    inline size_type tellg() const
    {
        return pos;
    }




    //pod type
    template<typename T>
    inline SerializableStream& operator << (const T& t)
    {
        buffer.append(&t, sizeof(t));

        return *this;
    }

    template<typename T>
    inline SerializableStream& operator >> (T& t)
    {
        uint8_t* p = (uint8_t*)&t;
        for(size_type i = 0; i < sizeof(t) && pos < buffer.size(); ++i)
        {
            *(p + i) = buffer.at(pos);
            ++pos;
        }
            
        return *this;
    }

    //std::string
    inline SerializableStream& operator << (const std::string& str)
    {
        (*this) << str.size();

        buffer.append(str.begin(), str.end());
        pos += str.size();

        return *this;
    }

    inline SerializableStream& operator >> (std::string& str)
    {
        std::string::size_t size = 0;
        (*this) >> size;
        
        buffer.sub_str(pos, size).swap(str);
        pos += size;

        return *this;
    }

    //std::pair
    template<typename T1, typename T2>
    inline SerializableStream& operator << (const std::pair<T1, T2>& pair)
    {
        (*this) << pair.first;
        (*this) << pair.second;

        return *this;
    }

    template<typename T1, typename T2>
    inline SerializableStream& operator >> (std::pair<T1, T2>& pair)
    {
        (*this) >> pair.first;
        (*this) >> pair.second;

        return *this;
    }

    //std::vector
    template<typename T>
    inline SerializableStream& operator << (const std::vector<T>& vec)
    {
        typename std::vector<T>::size_type size = vec.size();
        (*this) << size;

        for(const T& item : vec)
            (*this) << item;

        return *this;
    }

    template<typename T>
    inline SerializableStream& operator >> (std::vector<T>& vec)
    {
        typename std::vector<T>::size_type size = 0;
        (*this) >> size;

        vec.resize(size);
        for(typename std::vector<T>::size_type i = 0; i < size; ++i)
            (*this) >> vec[i];

        return *this;
    }

    //std::set
    template<typename T>
    inline SerializableStream& operator << (const std::set<T>& s)
    {
        typename std::set<T>::size_type size = s.size();
        (*this) << size;

        for(const T& item : s)
            (*this) << item;

        return *this;
    }

    template<typename T>
    inline SerializableStream& operator >> (std::set<T>& s)
    {
        s.clear();

        typename std::set<T>::size_type size = 0;
        (*this) >> size;

        for(typename std::set<T>::size_type i = 0; i < size; ++i)
        {
            T t;
            (*this) >> t;
            s.insert(s.end(), value)
        }

        return *this;
    }

private:
    Buffer buffer;
    size_type pos = 0;
};

#endif
