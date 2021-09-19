#ifndef PROJECT_DISCRIPTOR
#define PROJECT_DISCRIPTOR

#include <sys/unistd.h>
#include <iostream>
#include "Exceptions.hpp"

namespace Project {

class Descriptor {
private:
    int fd_;
    Descriptor &operator=(const Descriptor &) = delete;
    Descriptor(const Descriptor &) = delete;

public:
    Descriptor();
    explicit Descriptor(int);
    virtual ~Descriptor();
    Descriptor(Descriptor &&);
    Descriptor &operator=(int);
    Descriptor &operator=(Descriptor &&);
    operator bool() const;
    void close();
    int getFd() const;
    void setFd(int);
};

} // namespace Project

#endif