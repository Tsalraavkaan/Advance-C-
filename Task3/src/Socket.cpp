#include "Socket.hpp"

namespace Tasks {

Socket::Socket() : sock_fd_(-1) {}

Socket::Socket(int fd) : sock_fd_(fd) {}

Socket::Socket(Socket &&sock) : sock_fd_(std::move(sock.sock_fd_)) {}

Socket &Socket::operator=(Socket &&sock) {
    sock_fd_.set_fd(-1);
    sock.sock_fd_.set_fd(-1);
}

Socket::operator bool() const {
    return sock_fd_;
}

void Socket::set_fd(int fd) {
    sock_fd_.set_fd(fd);
}

int Socket::get_fd() {
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
void Socket::listen(int backlog) {
    if (sock_fd_) {
        if (::listen(sock_fd_.get_fd(), backlog) < 0) {
            throw Tasks::ConnectionError("Error in listening socket!");
        }
    }
}

void Socket::bind(const std::string &addr, uint16_t port) {
    sockaddr_in sock_addr{};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (::inet_aton(addr.c_str(), &sock_addr.sin_addr) == 0) {
        throw Tasks::BaseException("Invalid Ip address");
    }
    if (::bind(get_fd(), reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) < 0) {
        throw Tasks::ConnectionError("Error binding to socket!");
    }
}

void Socket::connect(const std::string &addr, uint16_t port) {
    if (*this) {
        throw Tasks::DescriptorError("Socket is already opened");
    }
    open();
    sockaddr_in sock_addr{};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (::inet_aton(addr.c_str(), &sock_addr.sin_addr) == 0) {
        throw Tasks::BaseException("Invalid Ip address");
    }
    if (::connect(get_fd(), reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) < 0) {
        throw ConnectionError("Error connecting to " + addr + " " + std::to_string(port));
    }
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

}//namespace Tasks