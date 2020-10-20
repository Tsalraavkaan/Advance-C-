#ifndef TASKS_SOCKET
#define TASKS_SOCKET

#include "Descriptor.hpp"
#include <sys/socket.h>

namespace Tasks {

class Socket : public Descriptor {
public:
    Socket();
    explicit Socket(int);
    ~Socket() = default;
    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;
    Socket(Socket &&);
    Socket &operator=(Socket &&);
    void open();
    void listen(int = SOMAXCONN);
};

} // namespace Tasks

#endif