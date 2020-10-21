#include <iostream>
#include "tcp.hpp"

int main(int argc, char *argv[]) {
    Tasks::Server server("127.127.127.127", 8888);
    std::cout << "accepting:" << std::endl;
    Tasks::Connection connection = server.accept();
    std::cout << "Accepting comlete" << std::endl;
    server.close();
    return 0;
}