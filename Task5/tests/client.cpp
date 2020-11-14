#include <iostream>
#include <random>
#include "net.hpp"

int main() {

    Tasks::tcp::Connection connection;
    connection.connect("127.0.0.1", 8083);
    connection.set_timeout(100);

    long long number;
    std::cout << "Input number:" << std::endl;
    std::cin >> number;
    int result;
    while(1) {
        connection.write(&number, sizeof(number));
        connection.read(&result, sizeof(result));
    }
    std::cout << result << std::endl;
    return 0;
}