#include "BufConnection.hpp"
#include <iostream>

namespace Tasks {

namespace net {

BufConnection::BufConnection(Service *service, tcp::Connection &&connection) :
        service_{service}, connection_{std::move(connection)} {}

void BufConnection::subscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(static_cast<unsigned>(flag) | static_cast<unsigned>(buf_flag_));
    service_->subscribeTo(connection_, buf_flag_);
}

void BufConnection::unsubscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(~(static_cast<unsigned>(flag)) & static_cast<unsigned>(buf_flag_));
    service_->unsubscribeFrom(connection_, buf_flag_);
}

std::string BufConnection::get_read_buf() const {
    return read_buf_;
}

std::string BufConnection::get_write_buf() const {
    return write_buf_;
}

size_t BufConnection::put_in_readbuf() {
    std::string buf(1024, '\0');
    size_t size = connection_.read(buf.data(), buf.size());
    buf.resize(size);
    read_buf_ += buf;
    return size;
}

size_t BufConnection::get_from_writebuf() {
    size_t size = connection_.write(write_buf_.data(), write_buf_.size());
    write_buf_.erase(0, size);
    return size;
}

void BufConnection::read(void *data, size_t len) {
    char *char_data = static_cast<char *>(data);
    std::copy(read_buf_.data(), read_buf_.data() + len, char_data);
    //std::cout << "Read buf: " << read_buf_ << std::endl;
}

void BufConnection::write(const void *data, size_t len) {
    const char *char_data = static_cast<const char *>(data);
    write_buf_ += std::string(char_data, char_data + len);
    std::cout << "Write buf: " << write_buf_.size() << std::endl;
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