#ifndef WATER_BASE_TOOLS_HPP
#define WATER_BASE_TOOLS_HPP

#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

namespace water{
namespace tool{

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


