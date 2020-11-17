#include "Socket.hpp"
#include "Exceptions.hpp"

namespace Tasks {

namespace tcp {

Socket::Socket() : sock_fd_{} {}

Socket::Socket(int fd) : sock_fd_(fd) {}

Socket::Socket(Socket &&sock) : sock_fd_(std::move(sock.sock_fd_)) {}

Socket &Socket::operator=(Socket &&sock) {
    sock_fd_ = std::move(sock.sock_fd_);
    sock.sock_fd_ = Descriptor(-1);
    return *this;
}

Socket::operator bool() const {
    return sock_fd_;
}

void Socket::set_fd(int fd) {
    sock_fd_.set_fd(fd);
}

int Socket::get_fd() const {
    return sock_fd_.get_fd();
}

void Socket::close() {
    sock_fd_.close();
}

void Socket::open() {
    if (sock_fd_) {
        throw Tasks::DescriptorError("Socket is already opened");
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        throw Tasks::DescriptorError("Error in opening socket!");
    }
    sock_fd_.set_fd(fd);
}

void Socket::set_timeout(size_t millisecond) {
    time_t seconds = millisecond / 1000;
    suseconds_t microsec = (millisecond % 1000) * 1000;
    timeval timeout{.tv_sec = seconds, .tv_usec = microsec};
    if (setsockopt(get_fd(), SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0 || 
            setsockopt(get_fd(), SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        throw Tasks::TimeoutError("Error in timeout");
    }
}

} // namespace tcp

}//namespace Tasks