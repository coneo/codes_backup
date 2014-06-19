#include "epoller.h"

#include <sys/epoll.h>
#include <linux/version.h>

#include "net_exception.h"

Epoller::Epoller()
: m_epollfd(::epoll_create(10))
{
    if(m_epollfd == -1)
        SYS_EXCEPTION(NetException, "::epoll_create");
}

Epoller::~Epoller()
{
}

void Epoller::regSocket(Socket* socket, EventType et, EventHanlder handler)
{
    if(socket == nullptr)
        return;

    struct epoll_event ev;
    ev.data.ptr = socket;

    if(et == EventType::READ)
    {
        ev.events = EPOLLIN;
        if(::epoll_ctl(m_epollfd, EPOLL_CTL_ADD, socket->getFD(), &ev) == -1)
            SYS_EXCEPTION(NetException, "::epoll_ctl");

        m_readEventHandlers[socket] = handler;
    }
    else// if(et == EventType::WRITE)
    {
        ev.events = EPOLLOUT;
        if(::epoll_ctl(m_epollfd, EPOLL_CTL_ADD, socket->getFD(), &ev) == -1)
            SYS_EXCEPTION(NetException, "::epoll_ctl");

        m_writeEventHandlers[socket] = handler;
    }
}

void EventHanlder::unregSocket(Socket* socket, EventHanlder et)
{
    if(socket == nullptr)
        return;

    struct epoll_event ev;
    ev.data.ptr = socket;

    if(et == EventType::READ)
    {
        ev.events = EPOLLIN;
        if(::epoll_ctl(m_epollfd, EPOLL_CTL_DEL, socket->getFD(), %ev) == -1)
            SYS_EXCEPTION(NetException, "::epoll_ctl");

        m_readEventHandlers.erase(socket);
    }
    else// if(et == EventType::WRITE)
    {
        ev.events = EPOLLOUT;
        if(::epoll_ctl(m_epollfd, EPOLL_CTL_DEL, socket->getFD(), %ev) == -1)
            SYS_EXCEPTION(NetException, "::epoll_ctl");

        m_writeEventHandlers.erase(socket);
    }
}

void EventHanlder::wait(int32_t timeout)
{
    if(socket == nullptr)
        return;

    const uint32_t maxevents = 100;
    struct epoll_event events[maxevents];

    const int32_t eventSize = ::epoll_wait(m_epollfd, &events, maxevents, timeout);
    if(eventSize == -1)
        SYS_EXCEPTION(NetException, "::epoll_wait");

    for(int32_t i = 0; i < eventSize; ++i)
    {
        if(events[i].events & EPOLL_OUT)
        {
            a
        }
        else //if(events[i].events & EPOLL_IN)
        {
            a
        }
    }

    for(;;) 
    {
        nfds = epoll_wait(m_epollfd, events, maxevents, -1);

        for(n = 0; n < nfds; ++n) 
        {
            if(events[n].data.fd == listener) 
            {
                client = accept(listener, (struct sockaddr *) &local,
                                &addrlen);
                if(client < 0){
                    perror("accept");
                    continue;
                }
                setnonblocking(client);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = client;
                if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, client, &ev) < 0) 
                {
                    fprintf(stderr, "epoll set insertion error: fd=%d\n",
                            client);
                    return -1;
                }
            }
            else
            {
                do_use_fd(events[n].data.fd);
            }
        }
    }
}

