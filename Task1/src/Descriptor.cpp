#include "Descriptor.hpp"

namespace Task1 {

    Descriptor::Descriptor() : fd_{-1} {}

    Descriptor::Descriptor(const int fd) : fd_{fd} {}

    Descriptor::~Descriptor() {
        if (this) {
            close();
        }
    }

    Descriptor &Descriptor::operator=(const int fd) {
        fd_ = fd;
        return *this;
    }

    void Descriptor::close() {
        if (fd_ == -1) {
            return;
        }
        if (::close(fd_) < 0) {
            throw Task1::DescriptorError("Error in closing desciptor");
        }
        fd_ = -1;
    }

    int Descriptor::getFd() const {
        return fd_;
    }

    Descriptor::operator bool() const {
        return fd_ != -1;
    }
}