#ifndef TASKS_SOCKET
#define TASKS_SOCKET

#include "Descriptor.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

namespace Tasks {

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
    int get_fd();
    void set_fd(int);
    void close();
    void open();
    void listen(int = SOMAXCONN);
    void bind(const std::string &, uint16_t);
    void connect(const std::string &, uint16_t);
    void set_timeout(size_t);
};

} // namespace Tasks

#endif