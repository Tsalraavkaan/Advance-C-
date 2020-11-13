#include <iostream>
#include "tcp.hpp"
#include <cstring>

int main(int argc, char *argv[]) {
    Tasks::tcp::Server server("127.127.127.127", 8088);
    std::cout << "accepting:" << std::endl;
    Tasks::tcp::Connection connection = server.accept();
    connection.set_timeout(1000);
    std::string str;
    size_t size;
    connection.readExact(&size, sizeof(size));
    str.resize(size);
    connection.readExact(str.data(), size);
    std::cout << str << std::endl;
    server.close();
    return 0;
}