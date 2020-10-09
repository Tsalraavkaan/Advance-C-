#ifndef TASK1_PROCESS
#define TASK1_PROCESS

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <string>
#include "Descriptor.hpp"

namespace Task1 {

    std::vector<char *> parseArgs(const std::string &, std::vector<std::string> &);

    class Process {
    private:
        std::string proc_path;
        pid_t proc_pid;
        Descriptor proc_in;
        Descriptor proc_out;

    public:
        Process(const std::string &, std::vector<std::string> &);
        ~Process() noexcept;
        size_t write(const void *, size_t);
        void writeExact(const void *, size_t);
        size_t read(void *, size_t);
        void readExact(void *, size_t);
        void closeStdin();
        void closeStdout();
        void close();
    };

}

#endif