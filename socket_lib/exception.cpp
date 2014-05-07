#include "exception.h"
#include <iostream>
#include <sstream>
#include <cxxabi.h>

#include <stdlib.h>
#include <execinfo.h>


using namespace std;



ExceptionBase(const std::string& info = "", 
              const char* file = "<unknown file>", 
              const char* func = "<unknown func>", 
              int line = -1) noexcept;

: m_info(info), m_file(file), m_func(func), m_line(-1), m_stackTraceSize(0)
{
    m_stackTraceSize = ::backtrace(mStackTrace, MAX_STACK_TRACE_SIZE);
}

ExceptionBase::~ExceptionBase() throw()
{
}

std::string ExceptionBase::className() const
{
    return "ExceptionBase";
}

const char* ExceptionBase::what() const throw()
{
    return m_info;
}

const std::string& ExceptionBase::toString() const
{
    if (!m_str.empty())
        return m_str;
    
    stringstream ss;
    if (mLine > 0)
        ss << m_file << "[" << m_line << "]";
    ss <<  "," << className();
    ss << ":\n";
    ss << m_info;
    ss << "call stack:\n";
    ss << stackTrace();

    m_str = ss.str();
   
    return m_str;
}

std::string ExceptionBase::stackTrace() const
{
    if (m_stackTraceSize == 0)
        return "<No stack trace>";
    char** strings = ::backtrace_symbols(m_stackTrace, MAX_STACK_TRACE_SIZE);
    if (strings == nullptr)
        return "<stack trace failure: backtrace_symbols returned nullptr>\n";

    std::string result;
    for (size_t i = 0; i < m_stackTraceSize; ++i)
    {
        std::string mangledName = strings[i];
        std::string::size_type begin = mangledName.find('(');
        std::string::size_type end = mangledName.find('+', begin);
        if (begin == std::string::npos || end == std::string::npos)
        {
            result += mangledName;
            result += '\n';
            continue;
        }

        ++begin;
        int status;
        char* s = abi::__cxa_demangle(mangledName.substr(begin, end-begin).c_str(), nullptr, 0, &status);

        if (status != 0)
        {
            result += mangledName;
            result += '\n';
            continue;
        }

        std::string demangledName(s);
        free(s);

        // Ignore ExceptionBase::Init so the top frame is the
        // user's frame where this exception is thrown.
        //
        // Can't just ignore frame#0 because the compiler might
        // inline ExceptionBase::Init.

        result += mangledName.substr(0, begin);

        result += demangledName;

        result += mangledName.substr(end);

        result += '\n';

    }

    free(strings);

    return result;

}
