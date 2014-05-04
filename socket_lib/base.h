#ifndef WATER_NET_BASE_HPP
#define WATER_NET_BASE_HPP

#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <netinet/in.h>      //struct sockaddr_in


#define STR(str) #str
#define MACRO_2_STR(str) STR(str)

#define TYPEDEF_PTR(ClassName) \
typedef std::shared_ptr<ClassName> Ptr;\
typedef std::shared_ptr<const ClassName> CPtr;\
typedef std::weak_ptr<ClassName> WPtr;\
typedef std::weak_ptr<const ClassName> CWPtr;

#define CREATE_FUN_NEW(ClassName)\
template <typename ... ArgsType>\
static std::shared_ptr<ClassName> create(ArgsType&& ... args)\
{\
    return std::shared_ptr<ClassName>(new ClassName(std::forward<ArgsType>(args)...));\
}

#define CREATE_FUN_MAKE(ClassName)\
template <typename ... ArgsType>\
static std::shared_ptr<ClassName> create(ArgsType&& ... args)\
{\
    return std::make_shared<ClassName>(std::forward<ArgsType>(args)...);\
}


namespace net
{

    struct IpV4
    {
        union
        {
            uint32_t value = 0;
            uint8_t bytes[4];
        };

        IpV4();
        std::string toString() const;
        void fromString(const std::string& str);
        static IpV4 getAddrByIfrName(const std::string& ifrName);
    };
    std::ostream& operator << (std::ostream& os, const IpV4& ip);
    std::istream& operator >> (std::istream& is, IpV4& ip);

    struct EndPoint
    {
        IpV4 ip;
        uint16_t port = 0;
    };

    namespace tool
    {
        template<typename T>
        std::string toString(const T& obj)
        {
            std::stringstream ss;
            ss << obj;
            return ss.str();
        }

        template <typename T>
        T fromString(const std::string& str)
        {
            T ret = T();
            std::stringstream ss(str);
            ss >> ret;
            return ret;
        }

        template <typename StrContiner>
        void splitString(StrContiner* result, const std::string& str, const std::string& delimiter)
        {
            if(result == nullptr)
                return;
            result->clear();
            std::string::size_type beginPos = 0;
            std::string::size_type endPos = 0;
            while(true)
            {
                endPos = str.find(delimiter, beginPos); //endPos此时指向分隔符

                if(endPos == std::string::npos)//没有剩余的分隔符了, 即切分完毕
                {
                    if(beginPos != endPos)// 最后一个分隔符不在串尾
                        result->insert(result->end(), str.substr(beginPos, endPos - beginPos));
                    break;
                }

                if(beginPos != endPos)// 当前位置的字符， 不是刚找到的分隔符
                    result->insert(result->end(), str.substr(beginPos, endPos - beginPos));

                beginPos = endPos + delimiter.length();
            }
        }
    }
}

#endif //ifndef WATER_NET_BASE_HPP


