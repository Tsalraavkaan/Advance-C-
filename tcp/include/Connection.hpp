#ifndef PROJECT_CONNECTION
#define PROJECT_CONNECTION

#include "Socket.hpp"
#include <sys/types.h>
#include <arpa/inet.h>

namespace Project {

namespace tcp {

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
    int get_fd() const;
};

} // namespace tcp

} //namespace Project

#endif