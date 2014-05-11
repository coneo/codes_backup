#ifndef WATER_NET_CONNECTOR_HPP
#define WATER_NET_CONNECTOR_HPP

#include "../base/component.h"
#include "endpoint.h"
#include "connection.h"

namespace water{
namespace net{
class TcpConnector
{

public:
    TYPEDEF_PTR(TcpConnector)
public:
    CREATE_FUN_MAKE(TcpConnector)
    TcpConnector(const std::string& strIp, uint16_t port);
    TcpConnector(const Endpoint& endPoint);

public:
    ~TcpConnector();

    TcpConnection::Ptr connect();

private:
    Endpoint m_remoteEndpoint;
};
}}

#endif
