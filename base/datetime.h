#ifndef WATER_TIME_POINT
#define WATER_TIME_POINT

/*
   独立于系统时区设定的时间记录计算工具
   不支持自动冬令时夏令时切换
   */

#include <cstdint>
#include <string>

namespace water
{


class TimePoint
{
public:
    struct Detail
    {
        int32_t year     = 0;
        int32_t month    = 0;
        int32_t day      = 0;
        int32_t hour     = 0;
        int32_t minute   = 0;
        int32_t second   = 0;
        int32_t weekday  = 0;
        int32_t yearday  = 0;
        int32_t offset   = 0;
    };

    TimePoint(uint64_t epochSeconds = 0, int32_t offset = 8);

    ~TimePoint();

    void setTimezone(int32_t offset);
    void setEpochMilliseconds(uint64_t epochSeconds);

    uint64_t epochMilliseconds() const;
    uint32_t epochSeconds() const;

    void setToNow();

    Detail detail() const;


    //格式化为字符串和从字符串逆格式化
    //格式为 YYYYMMDD-hh:mm:ss.UTC+timezoneoffset, 
    //如: 2014年1月2日12点30分30秒 东8区  :  "20140102-12:30:30.+28800"
    std::string toString() const;
    void fromString(const std::string& timeStr);

public:
    static TimePoint now(int32_t offset = 8);

private:
    void doGmtime() const;

private:
    uint64_t m_epochMilliseconds = 0;
    int32_t m_offset = 0;
    mutable tm* m_localtm = nullptr;
};



}

#endif
