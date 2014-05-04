#ifndef WATER_NET_SOCKET_IO_SELECTOR_HPP
#define WATER_NET_SOCKET_IO_SELECTOR_HPP


#include "base.h"
#include "socket.h"

#include <unordered_map>
#include <functional>

namespace net
{
//    typedef void eventHanlder(void*);
    typedef std::function<void (void*)> eventHanlder;

    class SocketIOSelector
    {
    public:
        CREATE_FUN(SocketIOSelector)

    private:
        SocketIOSelector();

    public:
        ~SocketIOSelector();

        void reg(TcpListener::Ptr listener, eventHanlder);
        void reg(TcpConnection::Ptr connection, eventHanlder);
        void unreg(Socket::Ptr 


    private:
        std::unordered_map<
    };
}


#endif
