#include "SharedMap.hpp"
#include <iostream>
#include <string>
#include <sys/wait.h>

int main()
{
    Tasks::shmem::SharedMap<int, std::string> map(10, 1024);
    std::string str = "A";
    char word = 'A';
    for (int i = 0; i < 10; ++i) {
        ++word;
        str += word;
        map.insert(i, str);
    }
    int pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid == 0) {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << " " <<  map.get(i) << std::endl;
        }
        map.insert(10, "QWERTY");
        map.update(3, "aaaaaaaa");
        map.remove(5);
        exit(0);
    }
    wait(NULL);
    for (int i = 0; i < 11; ++i) {
        try {
            std::cout << i << " " <<  map.get(i) << std::endl;
        } catch (Tasks::KeyError err) {
            std::cerr << "No element with key this key" << std::endl;
        }
    }
    return 0;
}
