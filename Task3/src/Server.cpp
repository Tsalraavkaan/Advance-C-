#include "Server.hpp"

namespace Tasks {

Server::Server() : sock_fd_{-1} {}

Server::Server(const std::string &addr, uint16_t port, int max_connection) : sock_fd_{-1} {
    open(addr, port, max_connection);
}

Server::Server(Server &&server) : sock_fd_{std::move(server.sock_fd_)} {
    server.sock_fd_.set_fd(-1);
}

Server &Server::operator=(Server &&server) {
    sock_fd_.set_fd(server.sock_fd_);
    server.sock_fd_.set_fd(-1);
    return *this;
}

void Server::set_timeout(size_t millisecond) {
    sock_fd_.set_timeout(millisecond);
}

void Server::open(const std::string &addr, uint16_t port, int max_connection) {
    sock_fd_.open();
    sockaddr_in sock_addr{};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (::inet_aton(addr.c_str(), &sock_addr.sin_addr) == 0) {
        throw Tasks::BaseException("Invalid Ip address");
    }
    if (::bind(sock_fd_.get_fd(), reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) < 0) {
        throw Tasks::ConnectionError("Error binding to socket!");
    }
    set_max_connection(max_connection);
}

Connection Server::accept() {
    sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    int client_fd = ::accept(sock_fd_.get_fd(), reinterpret_cast<sockaddr*>(&client_addr), &addr_size);
    if (client_fd < 0) {
        throw Tasks::ConnectionError("Error accepting connection!");
    }
    return Connection(client_fd);
}

void Server::close() {
    sock_fd_.close();
}

void Server::set_max_connection(int max_connection) {
    if (sock_fd_) {
        if (::listen(sock_fd_.get_fd(), max_connection) < 0) {
            throw Tasks::ConnectionError("Error in listening socket!");
        }
    }
}

}//namespace Tasks