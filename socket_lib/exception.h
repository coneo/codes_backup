#ifndef WATER_EXCEPTION_HPP
#define WATER_EXCEPTION_HPP

#include "base.h"
#include <string>
#include <cstring>
#include <memory>

typedef int32_t ErrorCode;


#include <exception>
#include <string>


#define EXCEPTION(ExClass, args...)\
do                                                         \
{                                                          \
    ExClass e(args);                                       \
    e.Init(__FILE__, __PRETTY_FUNCTION__, __LINE__);       \
    throw e;                                               \
}                                                          \
while (false)     


#define MY_DEFINE_EXCEPTION(ExClass, Base)                 \
ExClass(const std::string& msg = "") noexcept              \
: Base(msg)                                                \
{}                                                         \
~ExClass() noexcept {}                                     \
std::string GetClassName() const override                  \
{                                                          \
    return #ExClass;                                       \
}


class ExceptionBase : public std::exception
{
public:
    ExceptionBase(const std::string& msg = "", 
                  const char* file = "<unknown file>", 
                  const char* func = "<unknown func>", 
                  int line = 0) noexcept;
    virtual ~ExceptionBase() noexcept;

    virtual std::string className() const noexcept;
    const char* what() const noexcept override;
    const std::string& toString() const noexcept;

    std::string stackTrace() const noexcept;

protected:
    const std::string m_info;
    const char* m_file;
    const char* m_func;
    const int m_line;

private:
    enum { MAX_STACK_TRACE_SIZE = 50 };
    void* m_stackTrace[MAX_STACK_TRACE_SIZE];
    size_t m_stackTraceSize;
    mutable std::string m_str;
    mutable std::string m_stack;
};


#define THROW_EX(ExceptionType, args)\
do\
{\
    throw ExceptionType(what, 0,     __FILE__, MACRO_2_STR(__LINE__));\
} while(false);

#define THROW_EX_ERRNO(ExceptionType, what...)\
do\
{\
    throw ExceptionType(args, errno, __FILE__, MACRO_2_STR(__LINE__));\
} while(false);


#endif //#ifndef WATER_EXCEPTION_HPP
