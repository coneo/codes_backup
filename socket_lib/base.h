#ifndef WATER_NET_BASE_HPP
#define WATER_NET_BASE_HPP

#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>


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
}

#endif //ifndef WATER_NET_BASE_HPP


