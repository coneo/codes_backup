#ifndef WATER_NET_SOCKET_HPP
#define WATER_NET_SOCKET_HPP

#include "socket.h"
#include "connection.h"

namespace net
{

    class TcpListener
    {
        TcpListener();
    public:
        CREATE_FUN(TcpListener);
        typedef std::shared_ptr<TcpListener> Ptr;
    public:
//        explicit TcpListener(Socket::Ptr socket = nullptr);
        ~TcpListener();

        TcpConnection::Ptr accept();
        void listen(uint16_t port);
        void listen(const std::string& ipStr, uint16_t port);

    private:
        void bind();
    private:
        TcpSocket::Ptr m_socket;
    };

}
#endif //#ifndef WATER_NET_SOCKET_HPP
