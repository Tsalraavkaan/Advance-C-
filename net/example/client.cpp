#include <iostream>
#include <random>
#include "net.hpp"

int main() {

    Project::tcp::Connection connection;
    connection.connect("127.0.0.1", 8000);

    int number;
    std::cout << "Input number:" << std::endl;
    std::cin >> number;
    std::string num = std::to_string(number);
    connection.write(num.data(), sizeof(int));
    std::string result(1024, '\0');
    connection.read(result.data(), result.size());
    std::cout << result << std::endl;
    return 0;
}