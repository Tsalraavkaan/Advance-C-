#include "Descriptor.hpp"

namespace Tasks {

Descriptor::Descriptor() : fd_{-1} {}

Descriptor::Descriptor(int fd) : fd_{fd} {}

Descriptor::Descriptor(Descriptor &&desk) {
   std::swap(*this, desk);
}

Descriptor &Descriptor::operator=(Descriptor &&desk) {
    std::swap(*this, desk);
    return *this;
}

Descriptor::~Descriptor() {
    try {
        close();
    }
    catch (Tasks::DescriptorError &info) {
        std::cerr << info.what() << std::endl;
    }
}

Descriptor::operator bool() const {
    return fd_ != -1;
}

void Descriptor::close() {
    if (!*this) {
        return;
    }
    if (::close(fd_) < 0) {
        fd_ = -1;
        throw Tasks::DescriptorError("Error in closing desciptor");
    }
    fd_ = -1;
}

int Descriptor::get_fd() const {
    return fd_;
}

void Descriptor::set_fd(int fd) {
    close();
    fd_ = fd;
}

} // namespace Tasks