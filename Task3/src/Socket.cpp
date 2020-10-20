#include "Socket.hpp"

namespace Tasks {

Socket::Socket() : Descriptor() {
    open();
}

Socket::Socket(int fd) : Descriptor(fd) {}

Socket::Socket(Socket &&sock) : Descriptor(std::move(sock.get_fd())) {}

Socket &Socket::operator=(Socket &&sock) {
    set_fd(sock.get_fd());
    sock.set_fd(-1);
}

void Socket::open() {
    if (*this) {
        throw Tasks::DescriptorError("Socket is already opened");
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        throw Tasks::DescriptorError("Error in opening socket!");
    }
    set_fd(fd);
}
void Socket::listen(int backlog) {
    if (*this) {
        if (::listen(get_fd(), backlog) < 0) {
            throw Tasks::ConnectionError("Error in listening socket!");
        }
    }
}

}//namespace Tasks