#ifndef Project_Server
#define Project_Server

#include "Connection.hpp"
#include "Socket.hpp"

namespace Project {

namespace tcp {

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
    int get_fd() const;
};

} // namespace tcp

} //namespace Project

#endif