#include "endpoint.h"

#include "net_exception.h"
#include "../base/scope_guard.h"
#include "../base/tools.h"

#include <string>
#include <cstring>
#include <iostream>

#include <sys/socket.h>      //socket
#include <sys/ioctl.h>       //ioctl
#include <unistd.h>          //close
#include <linux/sockios.h>   //SIOCGIFADDR
#include <net/if.h>          //struct ifreq
#include <netinet/in.h>     //struct sockaddr_in

namespace water{
namespace net{


IpV4::IpV4()
:value(0)
{
}

std::string IpV4::toString() const
{
    std::stringstream ss;
    ss
    << (int)bytes[0] << "." 
    << (int)bytes[1] << "." 
    << (int)bytes[2] << "." 
    << (int)bytes[3];

    return ss.str();
}

void IpV4::fromString(const std::string& str)
{
    std::vector<std::string> items;
    tool::splitString(&items, str, ".");
    items.resize(4);

    bytes[0] = tool::fromString<int>(items[0]);
    bytes[1] = tool::fromString<int>(items[1]);
    bytes[2] = tool::fromString<int>(items[2]);
    bytes[3] = tool::fromString<int>(items[3]);
}

IpV4 IpV4::getAddrByIfrName(const std::string& ifrName)
{
    int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    ON_EXIT_SCOPE_DO( ::close(fd) );

    if(fd == -1)
        SYS_EXCEPTION(NetException, "::socket");

    struct ifreq ifr;
    std::memset(ifr.ifr_name, 0, sizeof(ifr.ifr_name));
    ifrName.copy(ifr.ifr_name, sizeof(ifr.ifr_name));

    if(::ioctl(fd, SIOCGIFADDR, &ifr) == -1)
        SYS_EXCEPTION(NetException, "::ioctl");

    IpV4 ip;
    ip.value = ((const struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr.s_addr;
    return ip;
}

std::ostream& operator << (std::ostream& os, const IpV4& ip)
{
    os << ip.toString();
    return os;
}

std::istream& operator >> (std::istream& is, IpV4& ip)
{
    std::string ipStr;
    is >> ipStr;
    ip.fromString(ipStr);
    return is;
}

namespace Tool
{

}

}} //namespace water::net


/*************************test**********************/
//g++ --std=c++11 -DUNIT_TEST base.cpp exception.cpp
#ifdef UNIT_TEST_BASE
#include <iostream>
#include <set>
using namespace std;

int main()
{
    try
    {

        auto ip = net::IpV4::getAddrByIfrName("enp0s3");
        cout << ip.toString() << "[" << ip.value << "]" << endl;

        net::IpV4 ip2;
        ip2.fromString("1.2.3.4");
        cout << ip2.value << endl;
        cout << ip2 << endl;
    }
    catch (net::NetException::Ptr ex)
    {
        cout << "errcode=" << ex->getErrorCode() << endl;
        cout << ex->errInfo() << endl;
    }
    return 0;
}

#endif
