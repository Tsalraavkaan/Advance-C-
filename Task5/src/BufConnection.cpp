#include "BufConnection.hpp"
#include "Exceptions.hpp"
#include <iostream>

namespace Tasks {

namespace net {

BufConnection::BufConnection(Service *service, tcp::Connection &&connection) :
        service_{service}, connection_{std::move(connection)} {
            read_buf_ = std::string();
            write_buf_ = std::string();
        }

void BufConnection::subscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(static_cast<unsigned>(flag) | static_cast<unsigned>(buf_flag_));
    service_->subscribeTo(connection_, buf_flag_);
}

void BufConnection::unsubscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(~(static_cast<unsigned>(flag)) & static_cast<unsigned>(buf_flag_));
    service_->unsubscribeFrom(connection_, buf_flag_);
}

std::string &BufConnection::get_read_buf() {
    return read_buf_;
}

std::string &BufConnection::get_write_buf() {
    return write_buf_;
}

tcp::Connection &BufConnection::get_connection() {
    return connection_;
}

EVENT_FLAG &BufConnection::get_flag() {
    return buf_flag_;
}

void BufConnection::close() {
    service_->closeConnection(connection_);
    connection_.close();
}

int BufConnection::get_fd() const {
    return connection_.get_fd();
}

} //namespace net

} //namespace Tasks