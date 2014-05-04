#include "connector.h"
#include "exception.h"
#include <cstring>


namespace net
{
    TcpConnector::TcpConnector(const std::string& strIp, uint16_t port)
    {
        m_remoteEndPoint.ip.fromString(strIp);
        m_remoteEndPoint.port = port;
    }

    TcpConnector::TcpConnector(const EndPoint& endPoint)
    : m_remoteEndPoint(endPoint)
    {
    }

    TcpConnector::~TcpConnector()
    {
    }

    TcpConnection::Ptr TcpConnector::connect()
    {
        struct sockaddr_in serverAddrIn;
        std::memset(&serverAddrIn, 0, sizeof(serverAddrIn));

        serverAddrIn.sin_family      = AF_INET;
        serverAddrIn.sin_addr.s_addr = m_remoteEndPoint.ip.value;
        serverAddrIn.sin_port        = htons(m_remoteEndPoint.port);

        TcpConnection::Ptr ret = TcpConnection::create(m_remoteEndPoint);
        if(-1 == ::connect(ret->getFD(), (const struct sockaddr*)&serverAddrIn, sizeof(serverAddrIn)))
            SYS_EXCEPTION(::connect);

        return ret;
    }
}
