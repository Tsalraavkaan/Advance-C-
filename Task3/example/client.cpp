#include <iostream>
#include "tcp.hpp"
#include <errno.h>

int main() {
    Tasks::Connection connection;
    connection.connect("127.1.1.1", 8888);
    connection.set_timeout(1000);
    std::cout << "Send information" << std::endl;
    connection.close();
    return 0;
}