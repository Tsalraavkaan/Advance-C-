#include <iostream>
#include "tcp.hpp"
#include <cstring>

int main() {
    Project::tcp::Connection connection;
    connection.connect("127.127.127.127", 8088);
    connection.set_timeout(1000);
    std::string str;
    size_t size;
    connection.readExact(&size, sizeof(size));
    str.resize(size);
    connection.readExact(str.data(), size);
    std::cout << str << std::endl;
    connection.close();
    return 0;
}