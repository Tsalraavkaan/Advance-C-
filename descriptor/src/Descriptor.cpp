#include "Descriptor.hpp"

namespace Project {

Descriptor::Descriptor() : fd_{-1} {}

Descriptor::Descriptor(const int fd) : fd_{fd} {}

Descriptor::~Descriptor() {
    try {
        close();
    }
    catch (Except::DescriptorError &info) {
        std::cerr << info.what() << std::endl;
    }
}
Descriptor::Descriptor(Descriptor &&desk) {
    fd_ = desk.fd_;
    desk.fd_ = -1;
}

Descriptor &Descriptor::operator=(Descriptor &&desk) {
    fd_ = desk.fd_;
    desk.fd_ = -1;
    return *this;
}

Descriptor &Descriptor::operator=(const int fd) { //////!!!!!!!
    close();
    fd_ = fd;
    return *this;
}

void Descriptor::close() {
    if (!*this) {
        return;
    }
    if (::close(fd_) < 0) {
        fd_ = -1;
        throw Except::DescriptorError("Error in closing desciptor");
    }
    fd_ = -1;
}

int Descriptor::getFd() const {
    return fd_;
}

void Descriptor::setFd(int fd) {
    close();
    fd_ = fd;
}

Descriptor::operator bool() const {
    return fd_ != -1;
}

} // namespace Project