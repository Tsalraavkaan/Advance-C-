#include "SharedMap.hpp"
#include <iostream>
#include <string>
#include <sys/wait.h>

int main()
{
    Tasks::SharedMap<std::string, std::string> map(1, 1024);
    map.insert("ABC", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    int pid = fork();
    if (pid < 0) {
        return 1;
    }
    else if (pid == 0) {
        std::cout << "ABC" << " " <<  map.get("ABC") << std::endl;
        map.insert("123", "1234567891011121314151617181920");
        map.update("ABC", "ABBACDDCEFFEGHHGIJJIABBACDDCEFFEGHHGIJJI");
    }
    else {
        wait(nullptr);
        std::cout << "123" << " " << map.get("123") << std::endl;
        std::cout << "ABC" << " " <<  map.get("ABC") << std::endl;
        map.remove("123");
        std::cout << "ABC" << " " <<  map.get("ABC") << std::endl;
    }
    return 0;
}
