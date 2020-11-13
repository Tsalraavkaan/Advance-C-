#include "BufConnection.hpp"

namespace Tasks {

namespace net {

BufConnection::BufConnection(Service *service, tcp::Connection &&connection) :
        service_{service}, connection_{std::move(connection)} {}

void BufConnection::subscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(static_cast<unsigned>(flag) | static_cast<unsigned>(buf_flag_));
    service_->subscribeTo(connection_, buf_flag_);
}

void BufConnection::unsubscribe(EVENT_FLAG flag) {
    buf_flag_ = static_cast<EVENT_FLAG>(~static_cast<unsigned>(flag) & static_cast<unsigned>(buf_flag_));
    service_->unsubscribeFrom(connection_, buf_flag_);
}

std::string BufConnection::get_read_buf() const {
    return read_buf_;
}

std::string BufConnection::get_write_buf() const {
    return write_buf_;
}

size_t BufConnection::put_in_read() {
    std::string buf(1024, '\0');
    size_t size = connection_.read(buf.data(), buf.size());
    buf.resize(size);
    read_buf_ += buf;
    return size;
}

size_t BufConnection::get_from_write() {
    size_t size = connection_.write(write_buf_.data(), write_buf_.size());
    write_buf_.erase(0, size);
    return size;
}

void BufConnection::read(void *data, size_t len) {
    char *char_data = static_cast<char *>(data);
    std::copy(write_buf_.data(), write_buf_.data() + len, char_data);
}

void BufConnection::write(const void *data, size_t len) {
    const char *char_data = static_cast<const char *>(data);
    write_buf_ += std::string(char_data, char_data + len);
}

void BufConnection::close() {
    connection_.close();
}

tcp::Descriptor BufConnection::get_Desc() const {
    return tcp::Descriptor(connection_.get_fd());
}

} //namespace net

} //namespace Tasks