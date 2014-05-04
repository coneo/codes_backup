#include "connection.h"
#include "exception.h"

namespace net
{
    TcpConnection::TcpConnection(const EndPoint& remoteEndPoint)
     : m_remoteEndPoint(remoteEndPoint), m_state(ConnState::READ_AND_WRITE)
    {
    }

    TcpConnection::TcpConnection(int32_t socketFD, bool nonBlocking, const EndPoint& remoteEndPoint)
     : TcpSocket(socketFD, nonBlocking), m_remoteEndPoint(remoteEndPoint), m_state(ConnState::READ_AND_WRITE)
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

    const EndPoint& TcpConnection::getRemoteEndPoint() const
    {
        return m_remoteEndPoint;
    }

    uint32_t TcpConnection::send(uint8_t* buf, int32_t bufLen)
    {
        return;
    }

    uint32_t TcpConnection::recv(uint8_t* buf, int32_t bufLen)
    {
        return;
    }

    void TcpConnection::shutdown(ConnState state)
    {
        if(!isAvaliable())
            return;

        switch (state)
        {
        case ConnState::READ:
        case ConnState::READ_AND_WRITE:
            ::shutdown(getFD(), SHUT_RD); //对读的关闭，因为可能影响对方行为，要生效到底层socket上
            break;
        case ConnState::WRITE:
            break;
        default:
            break;
        }

        const uint8_t m_stateValue = (uint8_t)m_state;
        const uint8_t stateValue = (uint8_t)state;
        m_state = (ConnState)(m_stateValue & ~stateValue);
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

}
