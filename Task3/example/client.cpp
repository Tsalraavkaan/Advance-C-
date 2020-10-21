#include <iostream>
#include "tcp.hpp"

int main() {
    Tasks::Connection connection;
    connection.connect("127.100.100.100", 8888);
    connection.set_timeout(10000);
    std::cout << "Send information" << std::endl;
    connection.close();
    return 0;
}