#ifndef TASK1_DISCRIPTOR
#define TASK1_DISCRIPTOR

#include <sys/unistd.h>
#include <iostream>

namespace Task1 {

    class Descriptor {
    private:
        int _fd;

    public:
        Descriptor();
        Descriptor(const int);
        ~Descriptor();
        Descriptor(const Descriptor &) = delete;
        Descriptor &operator=(const int);
        void close();
        int getFd() const;
        bool isExists() const;
    };

}

#endif