#ifndef TASKS_EVENTS_H
#define TASKS_EVENTS_H

#include <sys/epoll.h>

namespace Tasks {

namespace net {

enum class EVENT_FLAG {
    BASIC = EPOLLRDHUP,
    READ = EPOLLIN | EPOLLRDHUP,
    WRITE = EPOLLOUT | EPOLLRDHUP,
    RDW = EPOLLIN | EPOLLOUT | EPOLLRDHUP
};

} //namespace net

} //namespace Tasks

#endif