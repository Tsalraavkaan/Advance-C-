#ifndef TASKS_EPOLL_H
#define TASKS_EPOLL_H

#include "tcp.hpp"

#include "Events.hpp"
#include <sys/epoll.h>
#include <vector>

namespace Tasks {

namespace net {

class EPoll {
    tcp::Descriptor epfd;
public:
    EPoll();
    EPoll(EPoll &&) = default;
    EPoll &operator=(EPoll &&) = default;
    EPoll(const EPoll &) = delete;
    EPoll &operator=(const EPoll &) = delete;
    void mod(int, EVENT_FLAG) const;
    void add(int, EVENT_FLAG) const;
    void del(int) const;
    std::vector<::epoll_event> wait(int = 1000, int = 1024);
};

} //namespace net

} //namespace Tasks

#endif