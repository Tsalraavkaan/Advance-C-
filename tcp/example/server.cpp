#include <iostream>
#include "tcp.hpp"
#include <cstring>

int main(int argc, char *argv[]) {
    std::string str, temp;
    while(std::cin >> temp) {
        str += temp + " ";
    }
    Project::tcp::Server server("127.127.127.127", 8088);
    std::cout << "accepting:" << std::endl;
    Project::tcp::Connection connection = server.accept();
    connection.set_timeout(1000);
    size_t size = str.size();
    connection.writeExact(&size, sizeof(size));
    connection.writeExact(str.data(), str.size());
    server.close();
    return 0;
}