#ifndef WATER_NET_EPOLLER_H
#define WATER_NET_EPOLLER_H

#include "../base/component.h"
#include "socket.h"

#include <functional>

namespace water{
namespace net{


class Epoller
{
public:
    enum class EventType { READ, WRITE };
    typedef std::function<void (Socket*)> EventHanlder;

    TYPEDEF_PTR(Epoller)
    CREATE_FUN_MAKE(Epoller)
public:
    Epoller();
    ~Epoller();

    void regSocket(Socket* socket, EventType et, EventHanlder hanlder);
    void unregSocket(Socket* socket, EventType et);
    void wait(int32_t timeout);

private:
    int32_t m_epollfd = -1;

    std::unordered_map<Socket*, EventHanlder> m_readEventHandlers;
    std::unordered_map<Socket*, EventHanlder> m_writeEventHandlers;
};

}}

#endif
