#ifndef WATER_NET_CONNECTION_HPP
#define WATER_NET_CONNECTION_HPP

#include "socket.h"
#include "endpoint.h"

namespace water{
namespace net{

class TcpConnection : public TcpSocket
{
    friend class TcpListener;
    friend class TcpConnector;
public:
    TYPEDEF_PTR(TcpConnection)
private:
    CREATE_FUN_NEW(TcpConnection)
    explicit TcpConnection(const Endpoint& remoteEndpoint);
    explicit TcpConnection(int32_t socketFD, const Endpoint& remoteEndpoint);

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

    const Endpoint& getRemoteEndpoint() const;

    //send返回-1时，表示非阻塞的socket在发送时放弃等待返回
    uint32_t send(uint8_t* buf, int bufLen);
    uint32_t recv(uint8_t* buf, int bufLen);

    void shutdown(ConnState state = ConnState::READ_AND_WRITE);

    ConnState getState() const;

private:
    Endpoint m_remoteEndpoint;
    ConnState m_state;
};

}}

#endif
