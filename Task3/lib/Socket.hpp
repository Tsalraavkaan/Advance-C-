#ifndef TASKS_SOCKET
#define TASKS_SOCKET

#include "Descriptor.hpp"
#include <sys/socket.h>

namespace Tasks {

namespace tcp {

class Socket {
private:
    Descriptor sock_fd_;
public:
    Socket();
    explicit Socket(int);
    ~Socket() = default;
    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;
    Socket(Socket &&);
    Socket &operator=(Socket &&);
    operator bool() const;
    int get_fd() const;
    void set_fd(int);
    void close();
    void open();
    void set_timeout(size_t);
};

} // namespace tcp

} // namespace Tasks

#endif