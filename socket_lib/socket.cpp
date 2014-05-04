#include "socket.h"
#include "exception.h"
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>


namespace net
{
    TcpSocket::TcpSocket()
    : m_fd(::socket(PF_INET, SOCK_STREAM, 0)), m_nonBlocking(false), m_autoClose(true)
    {
    }

    TcpSocket::TcpSocket(int32_t fd, bool nonBlocking)
    : m_fd(fd), m_nonBlocking(nonBlocking), m_autoClose(true)
    {
    }

    TcpSocket::~TcpSocket()
    {
        try
        {
            if(m_autoClose)
                close();
        }
        catch(...)
        {
        }
    }


    void TcpSocket::close()
    {
        if(!isAvaliable())
            return;

        if(-1 == ::close(m_fd))
            SYS_EXCEPTION(::close);
        m_fd = TcpSocket::INVALID_SOCKET_FD;
    }



    int32_t TcpSocket::getFD() const
    {
        return m_fd;
    }

    bool TcpSocket::isAvaliable() const
    {
        return m_fd != INVALID_SOCKET_FD;
    }

    void TcpSocket::disableAutoClose()
    {
        m_autoClose = false;
    }

    bool TcpSocket::isNonBlocking() const
    {
        return m_nonBlocking;
    }

    void TcpSocket::setNonBlocking()
    {
        if(isNonBlocking())
            return;

        int32_t flag = 1;
        if(-1 == ::ioctl(getFD(), FIONBIO, (void *)&flag))
            SYS_EXCEPTION(::ioctl)

        m_nonBlocking = true;
    }

    void TcpSocket::bind(uint16_t port)
    {
        EndPoint endPoint;
        endPoint.ip.value = ::htonl(INADDR_ANY);
        endPoint.port     = port;

        bind(endPoint);
    }

    void TcpSocket::bind(const std::string& strIp, uint16_t port)
    {
        EndPoint endPoint;
        endPoint.ip.fromString(strIp);
        endPoint.port = port;

        bind(endPoint);
    }

    void TcpSocket::bind(const EndPoint& endPoint)
    {
        int32_t flag = 1;
        if(-1 == ::setsockopt(getFD(), SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)))
            SYS_EXCEPTION(::setsockopt);

        struct sockaddr_in serverAddrIn;
        memset(&serverAddrIn, 0, sizeof(serverAddrIn));

        serverAddrIn.sin_family = AF_INET;
        serverAddrIn.sin_addr.s_addr = endPoint.ip.value;
        serverAddrIn.sin_port = ::htons(endPoint.port);

        if(-1 == ::bind(getFD(), (const struct sockaddr*)&serverAddrIn, sizeof(serverAddrIn)))
            SYS_EXCEPTION(::bind);
    }
}
