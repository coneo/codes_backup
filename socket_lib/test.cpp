#include "listener.h"
#include "connector.h"
#include "connection.h"
#include "net_exception.h"

#include <iostream>
#include <string>
#include <memory>

#include <unistd.h> //sleep

using namespace std;

#ifdef TEST_SERVER
int main()
{
    try
    {
        auto listener = net::TcpListener::create();
        listener->bind(1024);
        listener->listen();

        cout << "server is running ..." << endl;
        
        auto connection = listener->accept();
        cout << "accept a client:" << connection->getRemoteEndpoint().ip
        << "[" << connection->getRemoteEndpoint().port << "]" << endl;

        ::sleep(30);
        connection->shutdown();
    }
    catch(net::NetException& ex)
    {
        cerr << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "unknown err" << endl;
    }
    return 0;
}

#endif

#ifdef TEST_CLIENT

int main()
{
    try
    {
        auto connector = net::TcpConnector::create("127.0.0.1", 1024);
        cout << "connect to server ..." << endl;
        auto connection = connector->connect();
        cout << "connected to server:" << connection->getRemoteEndpoint().ip << "[" << connection->getRemoteEndpoint().port << "]" << endl;
        ::sleep(30);
        connection->shutdown();
    }
    catch(net::NetException& ex)
    {
        cerr << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "unknown err" << endl;
    }
    return 0;
}



#endif
