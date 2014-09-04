#ifndef WATER_BASE_TOOLS_HPP
#define WATER_BASE_TOOLS_HPP

#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

namespace water{

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


//字符串分割， 不保留空串
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

//随机访问容器的尾删除
template <typename RandomContiner>
void tailEraseInRandomAccessContiner(RandomContiner* continer, typename RandomContiner::size_type index)
{
    typename RandomContiner::value_type tmp = continer->back();
    continer->back() = continer->at(index);
    continer->at(index) = continer->back();
}

//格式化字符串
namespace format
{/*
template <class T, typename CondType = typename enable_if<std::is_integral<T>::value, long>::type>
long normalizeArg(T arg) {
    return
    arg; }
    template
    <
    class
    T>
    typename
    enable_if<is_floating_point<T>::value,
    double
    >::type
    normalizeArg(T arg) {
        return
        arg; }
        template
        <
        class
        T>
        typename
        enable_if<is_pointer<T>::value, T>::type
        normalizeArg(T arg) {
            return
            arg; }
            const char
            * normalizeArg(
                           const
                           string& arg) {
                return
                arg.c_str();
            }
template <typename... ArgList>
std::string formart(const std::string& formart)
{

}
*/
}
}

#endif //ifndef WATER_NET_BASE_HPP


