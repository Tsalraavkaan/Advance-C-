#ifndef PROJECT_EPOLL
#define PROJECT_EPOLL

#include "tcp.hpp"

#include "Events.hpp"
#include <sys/epoll.h>
#include <vector>

namespace Project {

namespace net {

namespace EPOLL_CONSTS {
    const int DEF_TIMEOUT = 1000;
    const size_t DEF_MAXEVENTS = 1024;
}

class EPoll {
    Descriptor epfd;
public:
    EPoll();
    EPoll(EPoll &&) = default;
    EPoll &operator=(EPoll &&) = default;
    EPoll(const EPoll &) = delete;
    EPoll &operator=(const EPoll &) = delete;
    void mod(int, EVENT_FLAG) const;
    void add(int, EVENT_FLAG) const;
    void del(int) const;
    std::vector<::epoll_event> wait(int = EPOLL_CONSTS::DEF_TIMEOUT,
            size_t = EPOLL_CONSTS::DEF_MAXEVENTS) const;
};

} //namespace net

} //namespace Project

#endif