#ifndef WATER_NET_CONNECTION_HPP
#define WATER_NET_CONNECTION_HPP

#include <functional>
#include <memory>
#include "socket.h"
#include "base.h"


namespace net
{

    class TcpConnection : public TcpSocket
    {
        friend class TcpListener;
        friend class TcpConnector;
    public:
        TYPEDEF_PTR(TcpConnection)
    private:
        CREATE_FUN_NEW(TcpConnection)
        explicit TcpConnection(const EndPoint& remoteEndPoint);
        explicit TcpConnection(int32_t socketFD, bool nonBlocking, const EndPoint& remoteEndPoint);

    public:
        ~TcpConnection();

    public:
        enum class ConnState : uint8_t 
        {
            CLOSED         = 0x00, 
            READ           = 0x01, 
            WRITE          = 0x02, 
            READ_AND_WRITE = 0x03
        };

        const EndPoint& getRemoteEndPoint() const;

        uint32_t send(uint8_t* buf, int bufLen);
        uint32_t recv(uint8_t* buf, int bufLen);

        void shutdown(ConnState state = ConnState::READ_AND_WRITE);
        void close() override;

        ConnState getState() const;

    private:
        EndPoint m_remoteEndPoint;
        ConnState m_state;
    };


    typedef std::function<void()> SocketEventHandler;

}


#endif
