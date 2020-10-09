#include "Descriptor.hpp"

namespace Task1 {

    Descriptor::Descriptor() : _fd{-1} {}

    Descriptor::Descriptor(const int fd) : _fd{fd} {}

    Descriptor::~Descriptor() {
        if (isExists()) {
            close();
        }
    }

    Descriptor &Descriptor::operator=(const int fd) {
        _fd = fd;
        return *this;
    }

    void Descriptor::close() {
        if (_fd == -1) {
            return;
        }
        if (::close(_fd) < 0) {
            std::cerr << "Error in closing desciptor" << std::endl;
            exit(1);
        }
        _fd = -1;
    }

    int Descriptor::getFd() const {
        return _fd;
    }

    bool Descriptor::isExists() const {
        return _fd != -1;
    }
}