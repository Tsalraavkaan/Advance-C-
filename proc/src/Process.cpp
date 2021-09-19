#include "Process.hpp"

namespace Project {

Process::Process(const std::string& path, const std::vector<std::string> &argv) :
        proc_path_{path}, proc_pid_{0} {
    int pipe_in[2];
    if (pipe(pipe_in) < 0) {
        throw Except::PipeError("Error in creating pipe");
    }
    int pipe_out[2];
    if (pipe(pipe_out) < 0) {
        ::close(pipe_in[0]);
        ::close(pipe_in[1]);
        throw Except::PipeError("Error in creating pipe");
    }
    proc_pid_ = fork();
    if (proc_pid_ < 0) {
        ::close(pipe_in[1]);
        ::close(pipe_out[0]);
        ::close(pipe_in[0]);
        ::close(pipe_out[1]);
        throw Except::ProcessError("Error in making fork");
    } else if (!proc_pid_) {
        ::close(pipe_in[1]);
        ::close(pipe_out[0]);
        if(dup2(pipe_in[0], 0) < 0 || dup2(pipe_out[1], 1) < 0) {
            std::cerr << "Error in making descriptor duplicate" << std::endl;
            exit(1);
        }
        ::close(pipe_in[0]);
        ::close(pipe_out[1]);
        std::vector<std::string> copy{argv};
        std::string copy_path{path};
        std::vector<char *> char_argv;
        char_argv.push_back(copy_path.data());
        for (std::string& arg : copy) {
             char_argv.push_back(arg.data());
        }
        char_argv.push_back(nullptr);
        if (execvp(path.c_str(), char_argv.data()) < 0) {
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
    close();
}

size_t Process::write(const void *data, size_t len) {
    if (!proc_in_) {
        throw Except::DescriptorError("Write descriptor is closed");
    }
    ssize_t num_written = ::write(proc_in_.getFd(), data, len);
    if (num_written < 0) {
        throw Except::WritingError("Error writing into process");
    } else {
        return static_cast<size_t> (num_written);
    }

}

void Process::writeExact(const void *data, size_t len) {
    size_t num_written = 0;
    while(num_written != len) {
        num_written += write(static_cast<const char*>(data) + num_written, len - num_written);
    }
}

size_t Process::read(void *data, size_t len) {
    if (!proc_out_) {
        throw Except::DescriptorError("Read descriptor is closed");
    }
    ssize_t num_read = ::read(proc_out_.getFd(), data, len);
    if (num_read < 0) {
        throw Except::ReadingError("Error reading from process");
    } else {
        return static_cast<size_t> (num_read);
    }

}

void Process::readExact(void *data, size_t len) {
    size_t num_read = 0;
    while(num_read != len) {
        ssize_t recived = read(static_cast<char*>(data) + num_read, len - num_read);
        if (recived == 0) {
            throw Except::ReadingError("EOF is reached before comlete reading");
        }
        num_read += recived;
    }
}

void Process::closeStdin() {
    if (proc_in_) {
        proc_in_.close();
    }
}

void Process::close() {
    kill(proc_pid_, SIGKILL);
    if (proc_pid_) {
        waitpid(proc_pid_, nullptr, 0);
    }
}

} // namespace Project
