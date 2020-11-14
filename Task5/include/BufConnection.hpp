#ifndef TASKS_BUFCONNECTION_H
#define TASKS_BUFCONNECTION_H

#include <string>
#include <memory>
#include "tcp.hpp"

#include "Service.hpp"
#include "Events.hpp"
#include "Exceptions.hpp"

namespace Tasks {

namespace net {

class Service;

class BufConnection {
private:
    std::string read_buf_;
    std::string write_buf_;
    tcp::Connection connection_;
    Service *service_;
    EVENT_FLAG buf_flag_ = EVENT_FLAG::BASIC;

public:
    void subscribe(EVENT_FLAG);
    void unsubscribe(EVENT_FLAG);
    BufConnection(Service *, tcp::Connection &&);
    BufConnection &operator=(const BufConnection &) = delete;
    BufConnection(const BufConnection &) = delete;
    std::string get_read_buf() const;
    std::string get_write_buf() const;
    int get_fd() const;
    void close();
    size_t put_in_readbuf();
    size_t get_from_writebuf();
    void read(void *, size_t);
    void write(const void *, size_t);
};

} //namespace net

} //namespace Tasks

#endif