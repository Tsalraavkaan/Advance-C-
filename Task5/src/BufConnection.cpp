#include "BufConnection.hpp"
#include "Exceptions.hpp"
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

size_t BufConnection::read_buf_remains() const {
    return BUF_CONSTS::READ_BUF_SIZE - read_buf_offset_;
}

size_t BufConnection::write_buf_remains() const {
    return BUF_CONSTS::WRITE_BUF_SIZE - write_buf_offset_;
}

bool BufConnection::write_done() {
    if (write_done_) {
        write_done_ = false;
        return true;
    }
    return false;
}

size_t BufConnection::put_in_readbuf() {
    size_t size = connection_.read(read_buf_.data() + read_buf_offset_, read_buf_remains());
    read_buf_offset_ += size;
    return size;
}

size_t BufConnection::get_from_writebuf() {
    size_t size = connection_.write(write_buf_.data(), write_buf_offset_);
    size_t temp_size = write_buf_offset_ - size;
    std::array<char, BUF_CONSTS::READ_BUF_SIZE> temp;
    std::copy(write_buf_.begin() + size, write_buf_.begin() + write_buf_offset_, temp.begin());
    std::copy(temp.begin(), temp.begin() + temp_size, write_buf_.begin());
    write_buf_offset_ -= size;
    return size;
}

void BufConnection::read(void *data, size_t len) {
    char *char_data = static_cast<char *>(data);

    size_t data_len = std::min(read_buf_offset_, len);

    std::copy(read_buf_.begin(), read_buf_.begin() + data_len, char_data);
    size_t temp_size = read_buf_offset_ - data_len;
    std::array<char, BUF_CONSTS::WRITE_BUF_SIZE> temp;
    std::copy(read_buf_.begin() + data_len, read_buf_.begin() + read_buf_offset_, temp.begin());
    std::copy(temp.begin(), temp.begin() + temp_size, read_buf_.begin());
    read_buf_offset_ -= data_len;
}

void BufConnection::write(const void *data, size_t len) {
    const char *char_data = static_cast<const char *>(data);

    size_t data_len = std::min(write_buf_remains(), len);

    std::copy(char_data, char_data + data_len, write_buf_.begin() + write_buf_offset_);
    write_buf_offset_ += data_len;
    write_done_ = true;
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