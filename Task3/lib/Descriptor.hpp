#ifndef TASKS_DISCRIPTOR
#define TASKS_DISCRIPTOR

#include <sys/unistd.h>
#include <iostream>

namespace Tasks {

namespace tcp {

class Descriptor {
private:
    int fd_;

public:
    Descriptor();
    explicit Descriptor(int);
    virtual ~Descriptor();
    Descriptor(const Descriptor &) = delete;
    Descriptor &operator=(const Descriptor &) = delete;
    Descriptor &operator=(Descriptor &&);
    Descriptor(Descriptor &&);
    operator bool() const;
    void close();
    int get_fd() const;
    void set_fd(int);
};

} // namespace tcp

} // namespace Tasks

#endif