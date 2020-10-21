#include <iostream>
#include "tcp.hpp"

int main() {
    Tasks::Connection connection;
    connection.connect("127.127.127.127", 8888);
    connection.set_timeout(100000);
    std::cout << "Connection is established" << std::endl;
    connection.close();
    return 0;
}