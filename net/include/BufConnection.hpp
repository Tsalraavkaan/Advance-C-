#ifndef PROJECT_BUFCONNECTION
#define PROJECT_BUFCONNECTION

#include <memory>
#include <array>
#include "tcp.hpp"

#include "Service.hpp"
#include "Events.hpp"

namespace Project {

namespace net {

class Service;

namespace BUF_CONSTS {
    const int BUF_SIZE = 1024;
}

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
    ~BufConnection();
    BufConnection &operator=(BufConnection &&) = default;
    BufConnection(BufConnection &&) = default;
    BufConnection &operator=(const BufConnection &) = delete;
    BufConnection(const BufConnection &) = delete;
    size_t read_to_buf();
    size_t write_from_buf();
    int get_fd() const;
    void close();
    std::string &get_read_buf();
    std::string &get_write_buf();
    tcp::Connection &get_connection();
};

} //namespace net

} //namespace Project

#endif