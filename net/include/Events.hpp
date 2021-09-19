#ifndef PROJECT_EVENTS
#define PROJECT_EVENTS

#include <sys/epoll.h>

namespace Project {

namespace net {

enum class EVENT_FLAG {
    BASIC = 0,
    READ = EPOLLIN,
    WRITE = EPOLLOUT,
    RDW = EPOLLIN | EPOLLOUT
};

} //namespace net

} //namespace Project

#endif