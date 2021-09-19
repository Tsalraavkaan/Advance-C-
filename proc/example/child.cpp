#include <iostream>
#include <string>

using msg_size = uint64_t;

void put_size(const msg_size size) {
    std::cout.write(reinterpret_cast<const char*>(&size), sizeof(size));
    std::cout.flush();
}

msg_size get_size() {
    msg_size size = 0;
    std::cin.read(reinterpret_cast<char*>(&size), sizeof(size));
    return size;
}

int main(int argc, char* argv[]) {
    std::string message = "Message from parent!";
    put_size(static_cast<msg_size>(message.size()));
    std::cout << message << std::flush;

    msg_size size = get_size();
    std::string new_message(size, '\0');
    std::cin.read(new_message.data(), size);

    new_message = std::string("Child recieved ") + new_message;
    put_size(static_cast<msg_size>(new_message.size()));
    std::cout << new_message << std::flush;
    return 0;
}
