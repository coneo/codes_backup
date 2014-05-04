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

#include <exception>
#include <stdexcept>

template<typename T1, typename T2>
void print(const std::pair<T1, T2>& pair, const std::string& delimiter = " ");

template<typename Continer>
void print(const Continer& con, const std::string& delimiter = " ");

void print(const std::string& str, const std::string& delimiter = " ")
{
    std::cout << str << delimiter;
}

void print(const int& num, const std::string& delimiter = " ")
{
    std::cout << num << delimiter;
}

void print(const long& num, const std::string& delimiter = " ")
{
    std::cout << num << delimiter;
}

void print(const unsigned long& num, const std::string& delimiter = " ")
{
    std::cout << num << delimiter;
}

template<typename T1, typename T2>
void print(const std::pair<T1, T2>& pair, const std::string& delimiter = " ")
{
    std::cout << "{";
    print(pair.first, delimiter);
    std::cout << ',';
    print(pair.second, delimiter);
    std::cout << "}" << delimiter;
}

template<typename Continer>
void print(const Continer& con, const std::string& delimiter = " ")
{
    std::cout << "{";
    for(const auto& item : con)
        print(item, delimiter);
    std::cout << "}";
}
