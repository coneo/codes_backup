#ifndef WATER_NET_SOCKET_HPP
#define WATER_NET_SOCKET_HPP

#include "../base/component.h"
#include "endpoint.h"
namespace water{
namespace net{

class TcpSocket
{
public:
    enum class BlockingStatus {BLOCKING, NON_BLOCKING };

public:
    TYPEDEF_PTR(TcpSocket)
protected:
    explicit TcpSocket();
    explicit TcpSocket(int32_t fd, BlockingStatus blockingStatus);

public:
    virtual ~TcpSocket();

    //no copyable
    TcpSocket(const TcpSocket&) = delete;
    TcpSocket(TcpSocket&&) = delete;
    TcpSocket& operator = (const TcpSocket&) = delete;

    void bind(uint16_t port);
    void bind(const std::string& strIp, uint16_t port);
    void bind(const Endpoint& endPoint);

    void setNonBlocking();
    bool isNonBlocking() const;

    int32_t getFD() const;

    bool isAvaliable() const;

    void close();
    void disableAutoClose();

public:
    typedef Event<void (TcpSocket*)> OnClosedEvent;
    OnClosedEvent onClosed;

private:
    int32_t m_fd;
    BlockingStatus m_blockingStatus;
    bool m_autoClose;
};

}}
#endif //#ifndef WATER_NET_SOCKET_H
