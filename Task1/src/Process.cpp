#include "Process.hpp"

namespace Task1 {

    std::vector<char *> parseArgs(const std::string &path, std::vector<std::string> &argv) {
        std::vector<char *> res;
        res.push_back(const_cast<char*> (path.c_str()));
        for (auto str : argv) {
            res.push_back(const_cast<char*> (str.c_str()));
        }
        return res;
    }

    Process::Process(const std::string& path, std::vector<std::string> &argv) :
            proc_path{path}, proc_pid{0}, proc_in{0}, proc_out{0} {
        int pipe_in[2], pipe_out[2];
        if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
            std::cerr << "Error in creating pipe" << std::endl;
            exit(1);
        }
        proc_pid = fork();
        if (proc_pid < 0) {
            std::cerr << "Error in making fork" << std::endl;
            exit(1);
        } else if (!proc_pid) {
            ::close(pipe_in[1]);
            ::close(pipe_out[0]);
            if(dup2(pipe_in[0], 0) < 0 || dup2(pipe_out[1], 1) < 0) {
                std::cerr << "Error in making descriptor duplicate" << std::endl;
                exit(1);
            }
            ::close(pipe_in[0]);
            ::close(pipe_out[1]);
            if (execvp(path.c_str(), parseArgs(proc_path, argv).data()) < 0) {
                std::cerr << "Error in making process" << std::endl;
                exit(1);
            }
        } else {
            ::close(pipe_in[0]);
            ::close(pipe_out[1]);
            proc_in = pipe_in[1];
            proc_out = pipe_out[0];
        }
    }

    Process::~Process() noexcept {
        if (proc_pid) {
            if (waitpid(proc_pid, nullptr, 0) < 0) {
                std::cerr << "Error in child  process" << std::endl;
                exit(1);
            }
        }
    }

    size_t Process::write(const void *data, size_t len) {
        if (!proc_in.isExists()) {
            std::cerr << "Write descriptor is closed" << std::endl;
            exit(1);
        }
        ssize_t num_written = ::write(proc_in.getFd(), data, len);
        if (num_written < 0) {
            std::cerr << "Error writing into process" << std::endl;
            exit(1);
        } else {
            return static_cast<ssize_t> (num_written);
        }

    }

    void Process::writeExact(const void *data, size_t len) {
        ssize_t num_written = 0;
        while(num_written != len) {
            num_written += write(static_cast<const char*>(data) + num_written, len - num_written);
        }
    }

    size_t Process::read(void *data, size_t len) {
        if (!proc_out.isExists()) {
            std::cerr << "Read descriptor is closed" << std::endl;
            exit(1);
        }
        ssize_t num_read = ::read(proc_out.getFd(), data, len);
        if (num_read < 0) {
            std::cerr << "Error reading from process" << std::endl;
            exit(1);
        } else {
            return static_cast<ssize_t> (num_read);
        }

    }

    void Process::readExact(void *data, size_t len) {
        ssize_t num_read = 0;
        while(num_read != len) {
            ssize_t recived = read(static_cast<char*>(data) + num_read, len - num_read);
            if (recived == 0) {
                std::cerr << "EOF is reached before comlete reading" << std::endl;
                exit(0);
            }
            num_read += recived;
        }
    }

    void Process::closeStdin() {
        if (proc_in.isExists()) {
            proc_in.close();
        }
    }

    void Process::closeStdout() {
        if (proc_in.isExists()) {
            proc_in.close();
        }
    }

    void Process::close() {
        closeStdin();
        closeStdout();
    }
}
