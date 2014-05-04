#include "tcp_listener.h"
#include "exception.h"

namespace net
{
    /*
    TcpListener::TcpListener(Socket::Ptr socket_)
    m_socket(socket_)
    {
    }
    */

    TcpListener::TcpListener()
    : m_socket(std::make_shared<TcpSocket>())
    {
    }

    TcpListener::~TcpListener()
    {
    }

    TcpConnection::Ptr TcpListener::accept()
    {
        if(m_socket == nullptr || !m_socket->isAvaliable())
            EXCEPTION("invalid socket");

        struct sockaddr_in clientAddrIn;
        socklen_t clientAddrInSize = 0;
        int fd = ::accept(m_socket->getFD(), (struct sockaddr*)&clientAddrIn, &clientAddrInSize);
        if(-1 == fd)
           SYS_EXCEPTION(::accept);

        TcpSocket::Ptr socket = std::make_shared<TcpSocket>(fd);
        EndPoint remoteEndPoint;
        
        TcpConnection::Ptr ret = std::make_shared<TcpConnection>(socket, remoteEndPoint);
        return ret;
    }


    void TcpListener::listen(const std::string& ipStr, uint16_t port)
    {   
    }

    void TcpListener::listen(uint16_t port)
    {
        if(m_socket == nullptr || !m_socket->isAvaliable())
            EXCEPTION("invalid socket");

        struct sockaddr_in serverAddrIn;
        memset(&serverAddrIn, 0, sizeof(serverAddrIn));

        serverAddrIn.sin_family = AF_INET;
        serverAddrIn.sin_addr.s_addr = ::htonl(INADDR_ANY);
        serverAddrIn.sin_port = ::htons(port);

        if(-1 == ::bind(m_socket->getFD(), (const struct sockaddr*)&serverAddrIn, sizeof(serverAddrIn)))
            SYS_EXCEPTION(::bind);

        if(-1 == ::listen(m_socket->getFD(), 2000))
            SYS_EXCEPTION(::listen);
    }

    void TcpListener::bind()
    {
    }
}


/**********************************************/

#ifdef UNIST_TEST_LISTENER
int main()
{
    net::TcpListener::Ptr listener = net::TcpListener::create();
    return 0;
}






#endif
