#ifndef TASKS_EVENTS_H
#define TASKS_EVENTS_H

#include <sys/epoll.h>

namespace Tasks {

namespace net {

enum class EVENT_FLAG {
    BASIC = 0,
    READ = EPOLLIN,
    WRITE = EPOLLOUT,
    RDW = EPOLLIN | EPOLLOUT
};

} //namespace net

} //namespace Tasks

#endif