#ifndef TASK1_DISCRIPTOR
#define TASK1_DISCRIPTOR

#include <sys/unistd.h>
#include <iostream>
#include "Exceptions.hpp"

namespace Task1 {

class Descriptor {
private:
    int fd_;

public:
    Descriptor();
    explicit Descriptor(int);
    ~Descriptor();
    Descriptor(const Descriptor &) = delete;
    Descriptor &operator=(int);
    operator bool() const;
    void close();
    int getFd() const;
};

} // namespace Task1

#endif