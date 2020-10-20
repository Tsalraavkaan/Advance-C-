#ifndef TASKS_CONNECTION_H
#define TASKS_CONNECTION_H

#include "Exceptions.hpp"
#include "Socket.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

namespace Tasks {

class Connection {
private:
    Socket sock_fd_;
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;
public:
    Connection(int = -1);
    Connection(const std::string &, uint16_t = 8888);
    Connection(Connection &&);
    ~Connection() = default;
    Connection &operator=(Connection &&);
    void connect(const std::string &, uint16_t = 8888);
    void close();
    size_t write(const void *, size_t);
    void writeExact(const void *, size_t);
    size_t read(void *, size_t);
    void readExact(void *, size_t);
    void set_timeout(long);
};

} //namespace Tasks

#endif