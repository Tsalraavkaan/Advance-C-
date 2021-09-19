#ifndef Project_SOCKET
#define Project_SOCKET

#include "Descriptor.hpp"
#include <sys/socket.h>

namespace Project {

namespace tcp {

class Socket {
private:
    Descriptor sock_fd_;
    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;
public:
    Socket();
    explicit Socket(int);
    ~Socket() = default;
    Socket(Socket &&) = default;
    Socket &operator=(Socket &&);
    operator bool() const;
    int get_fd() const;
    void set_fd(int);
    void close();
    void open();
    void set_timeout(size_t);
};

} // namespace tcp

} // namespace Project

#endif