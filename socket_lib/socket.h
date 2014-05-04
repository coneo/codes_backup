#ifndef WATER_NET_SOCKET_HPP
#define WATER_NET_SOCKET_HPP

#include "base.h"

namespace net
{

    class TcpSocket
    {
    public:
        TYPEDEF_PTR(TcpSocket)
    protected:
        explicit TcpSocket();
        explicit TcpSocket(int32_t fd, bool nonBlocking);

    public:
        enum {INVALID_SOCKET_FD = -1};

    public:
        virtual ~TcpSocket();

        //no copyable
        TcpSocket(const TcpSocket&) = delete;
        TcpSocket(TcpSocket&&) = delete;
        TcpSocket& operator = (const TcpSocket&) = delete;

        void bind(uint16_t port);
        void bind(const std::string& strIp, uint16_t port);
        void bind(const EndPoint& endPoint);

        void setNonBlocking();
        bool isNonBlocking() const;

        int32_t getFD() const;

        bool isAvaliable() const;

        virtual void close();
        void disableAutoClose();


    private:
        int32_t m_fd;
        bool m_nonBlocking;
        bool m_autoClose;
    };

}

#endif //#ifndef WATER_NET_SOCKET_H
