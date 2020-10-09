#include "../lib/Descriptor.hpp"

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

#include "../lib/Process.hpp"

namespace Task1 {

    std::vector<char *> parseArgs(const std::string &path, std::vector<std::string> &argv) {
        std::vector<char *> res;
        res.push_back(const_cast<char*> (path.c_str()));
        for (auto str : argv) {
            res.push_back(const_cast<char*> (str.c_str()));
        }
        res.push_back(nullptr);
        return res;
    }

    Process::Process(const std::string &path, std::vector<std::string> &argv) :
            proc_path{path}, proc_pid{0}, proc_in{-1}, proc_out{-1} {
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
            if (execvp(proc_path.c_str(), parseArgs(proc_path, argv).data()) < 0) {
                std::cerr << "Error in making process" << errno << std::endl;
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

    void Process::close() {
        if (proc_in.isExists()) {
            proc_in.close();
        }
        if (proc_out.isExists()) {
            proc_out.close();
        }
    }
}

using msg_size = uint64_t;

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cerr << "First argument must be process path!" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::vector<std::string> child_args;
    for (int i = 1; i < argc; ++i) {
        child_args.push_back(argv[i]);
    }

    Task1::Process proc(path, child_args);
    
    std::string message;
    msg_size size;

    proc.readExact(&size, sizeof(size));
    message.resize(size);
    proc.readExact(message.data(), size);
    std::cout << "Parent recieved " << message << std::endl;


    message = "Hello, child!";
    std::cout << "Sending message to child" << std::endl;
    msg_size to_send = static_cast<msg_size>(message.size());
    proc.writeExact(&to_send, sizeof(to_send));
    proc.writeExact(message.data(), to_send);


    proc.readExact(&size, sizeof(size));
    message.resize(size);
    proc.readExact(message.data(), size);
    std::cout << "Parent recieved " << message << std::endl;

    return 0;
}