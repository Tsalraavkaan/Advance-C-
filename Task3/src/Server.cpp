#include "Server.hpp"
#include <errno.h>
#include <string.h>

namespace Tasks {

Server::Server() : sock_fd_{-1} {}

Server::Server(const std::string &addr, uint16_t port, int max_connection) : sock_fd_{-1} {
    open(addr, port, max_connection);
}

Server::Server(Server &&server) : sock_fd_{std::move(server.sock_fd_.get_fd())} {
    server.sock_fd_.set_fd(-1);
}

Server &Server::operator=(Server &&server) {
    sock_fd_.set_fd(server.sock_fd_.get_fd());
    server.sock_fd_.set_fd(-1);
    return *this;
}

void Server::set_timeout(long microsec) {
    timeval timeout{.tv_sec = 0, .tv_usec = microsec};
    if (setsockopt(sock_fd_.get_fd(), SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0 || 
            setsockopt(sock_fd_.get_fd(), SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        throw Tasks::TimeoutError("Error in timeout");
    }

}

void Server::open(const std::string &addr, uint16_t port, int max_connection) {
    sock_fd_.open();
    sock_fd_.listen(max_connection);

    sockaddr_in sock_addr{};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (::inet_aton(addr.c_str(), &sock_addr.sin_addr) == 0) {
        throw Tasks::BaseException("Invalid Ip address");
    }
    if (::bind(sock_fd_.get_fd(), reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) < 0) {
        std::cout << addr << " " << port << std::endl;
        std::cout << (errno == EINVAL) << " " << strerror(errno) << std::endl;
        throw Tasks::ConnectionError("Error binding to socket!");
    }
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
    sock_fd_.listen(max_connection);
}

}//namespace Tasks