#include "connection.h"

#include "net_exception.h"

#include <sys/socket.h>

namespace water{
namespace net{

TcpConnection::TcpConnection(const Endpoint& remoteEndpoint)
: m_remoteEndpoint(remoteEndpoint), m_state(ConnState::READ_AND_WRITE)
{
}

TcpConnection::TcpConnection(int32_t socketFD, BlockingStatus blockingStatus, const Endpoint& remoteEndpoint)
: TcpSocket(socketFD, blockingStatus), m_remoteEndpoint(remoteEndpoint), m_state(ConnState::READ_AND_WRITE)
{
}

TcpConnection::~TcpConnection()
{
    try
    {
        if(getState() != ConnState::CLOSED)
            close();
    }
    catch(...)
    {
    }
}

const Endpoint& TcpConnection::getRemoteEndpoint() const
{
    return m_remoteEndpoint;
}

uint32_t TcpConnection::send(uint8_t* buf, int32_t bufLen)
{
    return 0;
}

uint32_t TcpConnection::recv(uint8_t* buf, int32_t bufLen)
{
    return 0;
}

void TcpConnection::shutdown(ConnState state)
{
    if(!isAvaliable())
        return;

    switch (state)
    {
    case ConnState::READ:
        ::shutdown(getFD(), SHUT_RD);
    case ConnState::WRITE:
        ::shutdown(getFD(), SHUT_WR);
        break;
    case ConnState::READ_AND_WRITE:
        ::shutdown(getFD(), SHUT_RDWR);
        break;
    default:
        break;
    }

    const uint8_t stateValue = (uint8_t)state;
    const uint8_t m_stateValue = (uint8_t)m_state;
    m_state = (ConnState)(m_stateValue & ~stateValue);

    if(m_state == ConnState::CLOSED)
        close();
}

void TcpConnection::close()
{
    shutdown(ConnState::READ_AND_WRITE);
    TcpSocket::close();
}

TcpConnection::ConnState TcpConnection::getState() const
{
    return m_state;
}

}}
