#ifndef WATER_NET_LISTENER_HPP
#define WATER_NET_LISTENER_HPP

#include "socket.h"
#include "connection.h"

namespace net
{

    class TcpListener : public TcpSocket
    {
    public:
        TYPEDEF_PTR(TcpListener);
    public:
        CREATE_FUN_MAKE(TcpListener);
        explicit TcpListener();

    public:
        ~TcpListener();

        void listen(int32_t backlog = 20);
        TcpConnection::Ptr accept();

    private:
    };

}
#endif //#ifndef WATER_NET_LISTENER_HPP
