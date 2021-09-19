#include "Connection.hpp"
#include "Exceptions.hpp"
#include <cstring>
#include <string>

namespace Project {

namespace tcp {

Connection::Connection(int fd) : sock_fd_{fd} {}

Connection::Connection(const std::string &addr, uint16_t port) : sock_fd_{} {
    connect(addr, port);
}

Connection::Connection(Connection &&connection) :
        sock_fd_{std::move(connection.sock_fd_)} {}

Connection &Connection::operator=(Connection &&connection) {
    sock_fd_ = std::move(connection.sock_fd_);
    return *this;
}

void Connection::set_timeout(size_t millisecond) {
    sock_fd_.set_timeout(millisecond);
}

void Connection::connect(const std::string &addr, uint16_t port) {
    if (sock_fd_) {
        throw Except::DescriptorError("Socket is already opened");
    }
    sockaddr_in sock_addr{};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (::inet_aton(addr.c_str(), &sock_addr.sin_addr) == 0) {
        throw Except::BaseException("Invalid Ip address");
    }
    sock_fd_.open();
    if (::connect(sock_fd_.get_fd(), reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) < 0) {
        sock_fd_.close();
        throw Except::ConnectionError("Error connecting to " + addr + " " + std::to_string(port));
    }
}

int Connection::get_fd() const {
    return sock_fd_.get_fd();
}

void Connection::close() {
    sock_fd_.close();
}

size_t Connection::write(const void *data, size_t len) {
    if (!sock_fd_) {
        throw Except::DescriptorError("Write descriptor is closed");
    }
    ssize_t num_written = ::write(sock_fd_.get_fd(), data, len);
    if (num_written < 0) {
        throw Except::WritingError("Error writing into process");
    }
    return static_cast<size_t> (num_written);
}

void Connection::writeExact(const void *data, size_t len) {
    size_t num_written = 0;
    while(num_written != len) {
        num_written += write(static_cast<const char*>(data) + num_written, len - num_written);
    }
}

size_t Connection::read(void *data, size_t len) {
    if (!sock_fd_) {
        throw Except::DescriptorError("Read descriptor is closed");
    }
    ssize_t num_read = ::read(sock_fd_.get_fd(), data, len);
    if (num_read < 0) {
        std::string str = "Error reading from process errno: ";
        throw Except::ReadingError(str + std::strerror(errno));
    } else {
        return static_cast<size_t> (num_read);
    }

}

void Connection::readExact(void *data, size_t len) {
    size_t num_read = 0;
    while(num_read != len) {
        size_t recived = read(static_cast<char*>(data) + num_read, len - num_read);
        if (recived == 0) {
            throw Except::ReadingError("EOF is reached before comlete reading");
        }
        num_read += recived;
    }
}

} // namespace tcp

} //namespace Project