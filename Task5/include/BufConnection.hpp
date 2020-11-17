#ifndef TASKS_BUFCONNECTION_H
#define TASKS_BUFCONNECTION_H

#include <memory>
#include <array>
#include "tcp.hpp"

#include "Service.hpp"
#include "Events.hpp"

namespace Tasks {

namespace net {

class Service;

namespace BUF_CONSTS {
    const unsigned long long READ_BUF_SIZE = 1024;
    const unsigned long long WRITE_BUF_SIZE = 1024;
};

class BufConnection {
private:
    std::array<char, BUF_CONSTS::READ_BUF_SIZE> read_buf_;
    std::array<char, BUF_CONSTS::WRITE_BUF_SIZE> write_buf_;
    size_t read_buf_offset_ = 0;
    size_t write_buf_offset_ = 0;
    bool write_done_ = false;
    tcp::Connection connection_;
    Service *service_;
    EVENT_FLAG buf_flag_ = EVENT_FLAG::BASIC;

public:
    void subscribe(EVENT_FLAG);
    void unsubscribe(EVENT_FLAG);
    BufConnection(Service *, tcp::Connection &&);
    BufConnection &operator=(const BufConnection &) = delete;
    BufConnection(const BufConnection &) = delete;
    size_t read_buf_remains() const;
    size_t write_buf_remains() const;
    int get_fd() const;
    bool write_done();
    void close();
    size_t put_in_readbuf();
    size_t get_from_writebuf();
    void read(void *, size_t);
    void write(const void *, size_t);
};

} //namespace net

} //namespace Tasks

#endif