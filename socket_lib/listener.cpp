#include "listener.h"
#include "exception.h"

namespace net
{
    TcpListener::TcpListener()
    {
    }

    TcpListener::~TcpListener()
    {
    }

    void TcpListener::listen(int32_t backlog)
    {
        if(-1 == ::listen(getFD(), backlog))
            SYS_EXCEPTION(::listen);
    }

    TcpConnection::Ptr TcpListener::accept()
    {
        struct sockaddr_in clientAddrIn;
        socklen_t clientAddrInSize = sizeof(clientAddrIn);

        int32_t fd = ::accept(getFD(), (struct sockaddr*)&clientAddrIn, &clientAddrInSize);
        if(-1 == fd)
            SYS_EXCEPTION(::accept);

        EndPoint remoteEndPoint;
        remoteEndPoint.ip.value = clientAddrIn.sin_addr.s_addr;     //远端ip
        remoteEndPoint.port     = ::ntohs(clientAddrIn.sin_port);   //远端port
        
        TcpConnection::Ptr ret = TcpConnection::create(fd, false, remoteEndPoint);
        return ret;
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
