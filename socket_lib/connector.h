#ifndef WATER_NET_CONNECTOR_HPP
#define WATER_NET_CONNECTOR_HPP

#include "base.h"
#include "connection.h"


namespace net
{
    class TcpConnector
    {

    public:
        TYPEDEF_PTR(TcpConnector)
    public:
        CREATE_FUN_MAKE(TcpConnector)
        TcpConnector(const std::string& strIp, uint16_t port);
        TcpConnector(const EndPoint& endPoint);

    public:
        ~TcpConnector();

        TcpConnection::Ptr connect();

    private:
        EndPoint m_remoteEndPoint;
    };
}

#endif
