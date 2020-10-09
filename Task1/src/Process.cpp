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
            proc_path_{path}, proc_pid_{0} {
        int pipe_in[2], pipe_out[2];
        if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
            ::close(pipe_in[1]);
            ::close(pipe_out[0]);
            ::close(pipe_in[0]);
            ::close(pipe_out[1]);
            throw Task1::PipeError("Error in creating pipe");
        }
        proc_pid_ = fork();
        if (proc_pid_ < 0) {
            throw Task1::ProcessError("Error in making fork");
        } else if (!proc_pid_) {
            ::close(pipe_in[1]);
            ::close(pipe_out[0]);
            if(dup2(pipe_in[0], 0) < 0 || dup2(pipe_out[1], 1) < 0) {
                std::cerr << "Error in making descriptor duplicate" << std::endl;
                exit(1);
            }
            ::close(pipe_in[0]);
            ::close(pipe_out[1]);
            if (execvp(path.c_str(), parseArgs(proc_path_, argv).data()) < 0) {
                std::cerr << "Error in making process" << std::endl;
                exit(1);
            }
        } else {
            ::close(pipe_in[0]);
            ::close(pipe_out[1]);
            proc_in_ = pipe_in[1];
            proc_out_ = pipe_out[0];
        }
    }

    Process::~Process() {
        kill(proc_pid_, SIGKILL);
        if (proc_pid_) {
            if (waitpid(proc_pid_, nullptr, 0) < 0) {
                std::cerr << "Error in child  process" << std::endl;
                exit(1);
            }
        }
    }

    size_t Process::write(const void *data, size_t len) {
        if (!proc_in_) {
            throw Task1::DescriptorError("Write descriptor is closed");
        }
        ssize_t num_written = ::write(proc_in_.getFd(), data, len);
        if (num_written < 0) {
            throw Task1::WritingError("Error writing into process");
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
        if (!proc_out_) {
            throw Task1::DescriptorError("Read descriptor is closed");
        }
        ssize_t num_read = ::read(proc_out_.getFd(), data, len);
        if (num_read < 0) {
            throw Task1::ReadingError("Error reading from process");
        } else {
            return static_cast<ssize_t> (num_read);
        }

    }

    void Process::readExact(void *data, size_t len) {
        ssize_t num_read = 0;
        while(num_read != len) {
            ssize_t recived = read(static_cast<char*>(data) + num_read, len - num_read);
            if (recived == 0) {
                throw Task1::ReadingError("EOF is reached before comlete reading");
            }
            num_read += recived;
        }
    }

    void Process::closeStdin() {
        if (proc_in_) {
            proc_in_.close();
        }
    }

    void Process::closeStdout() {
        if (proc_out_) {
            proc_out_.close();
        }
    }

    void Process::close() {
        closeStdin();
        closeStdout();
    }
}
