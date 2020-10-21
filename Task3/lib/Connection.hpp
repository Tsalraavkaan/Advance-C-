#ifndef TASKS_CONNECTION_H
#define TASKS_CONNECTION_H

#include "Exceptions.hpp"
#include "Socket.hpp"

namespace Tasks {

class Connection {
private:
    Socket sock_fd_;
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;
public:
    Connection() = default;
    Connection(int);
    Connection(const std::string &, uint16_t);
    Connection(Connection &&);
    ~Connection() = default;
    Connection &operator=(Connection &&);
    void connect(const std::string &, uint16_t);
    void close();
    size_t write(const void *, size_t);
    void writeExact(const void *, size_t);
    size_t read(void *, size_t);
    void readExact(void *, size_t);
    void set_timeout(size_t);
};

} //namespace Tasks

#endif