#ifndef WATER_EXCEPTION_HPP
#define WATER_EXCEPTION_HPP

#include "base.h"
#include <string>
#include <cstring>
#include <memory>

namespace net
{


    typedef int32_t ErrorCode;

    class NetException// : public std::exception
    {
    public:
        typedef std::shared_ptr<NetException> Ptr;
    public:
        NetException(const std::string& desc_, ErrorCode ec, const std::string& file_, const std::string& line_) noexcept
        :desc(desc_), errorCode(ec), file(file_), line(line_)
        {
        }

        inline const std::string& getDesc() const noexcept
        {
            return desc;
        }

        inline const std::string& getFile() const noexcept
        {
            return file;
        }

        inline const std::string& getLine() const noexcept
        {
            return line;
        }

        inline ErrorCode getErrorCode() const noexcept
        {
            return errorCode;
        }

        inline std::string errInfo() const noexcept
        {
            return file + "+" + line + " [" + desc + "] {" + tool::toString(errorCode) + ":" + std::strerror(errorCode) + "}";
        }
    private:
        const std::string desc;
        const std::string file;
        const std::string line;
        const ErrorCode errorCode;
    };

#define EXCEPTION(errdesc) throw std::make_shared<NetException>(errdesc, 0, __FILE__, MACRO_2_STR(__LINE__));
#define SYS_EXCEPTION(syscall) throw std::make_shared<NetException>(#syscall, errno, __FILE__, MACRO_2_STR(__LINE__));

}

#endif //#ifndef WATER_EXCEPTION_HPP
