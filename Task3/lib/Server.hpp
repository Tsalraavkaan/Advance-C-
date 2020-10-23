#ifndef TASKS_Server_H
#define TASKS_Server_H

#include "Exceptions.hpp"
#include "Connection.hpp"
#include "Socket.hpp"

namespace Tasks {

class Server {
private:
    Socket sock_fd_;
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;
public:
    Server() = default;
    Server(const std::string &, uint16_t, int = SOMAXCONN);
    Server(Server &&);
    Server &operator=(Server &&);
    void open(const std::string &, uint16_t, int = SOMAXCONN);
    Connection accept();
    void close();
    void set_timeout(size_t);
    void set_max_connection(int);
};

} //namespace Tasks

#endif