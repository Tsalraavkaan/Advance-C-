#include "Process.hpp"

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

    Project::Process proc(path, child_args);
    
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