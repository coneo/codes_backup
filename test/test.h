#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <memory>
#include <functional>

#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <string>
#include <sstream>

#include <list>
#include <forward_list>

#include <exception>
#include <stdexcept>


template<typename T1, typename T2>
std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& pair)
{
    os << "{";
    os << pair.first << " ";
    os << ',';
    os << pair.second << " ";
    os << "}" << " ";
}


#define SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(Container) \
template<typename T>\
std::ostream& operator << (std::ostream& os, const Container<T>& con)\
{\
    os << "{";\
    for(const auto& item : con)\
        os << item << " ";\
    os << "}";\
    return os;\
}

#define ASSOCIATIVE_CONTAINER_OSTREAM_OPERATOR(Container) \
template<typename T1, typename T2>\
std::ostream& operator << (std::ostream& os, const Container<T1, T2>& con)\
{\
    os << "{";\
    for(const auto& item : con)\
        os << item << " ";\
    os << "}";\
    return os;\
}

ASSOCIATIVE_CONTAINER_OSTREAM_OPERATOR(std::map)
ASSOCIATIVE_CONTAINER_OSTREAM_OPERATOR(std::multimap)
ASSOCIATIVE_CONTAINER_OSTREAM_OPERATOR(std::unordered_map)
ASSOCIATIVE_CONTAINER_OSTREAM_OPERATOR(std::unordered_multimap)

SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::set)
SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::multiset)
SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::unordered_set)
SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::unordered_multiset)

SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::vector)

SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::list)
SENQUENTIAL_CONTAINER_OSTREAM_OPERATOR(std::forward_list)
