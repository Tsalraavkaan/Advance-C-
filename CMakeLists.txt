cmake_minimum_required(VERSION 3.10.2)
project(TechnoSphere)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_compile_options( -W  -Wall      -pedantic       -fstack-protector-all
                     -Wextra        -Wfloat-equal
                     -Wcast-align   -Wpointer-arith -Wformat-security
                     -Wformat       -Wwrite-strings -Wcast-align
                     -Wno-long-long -Wunused        -Wcast-qual)

add_subdirectory(descriptor)
add_subdirectory(proc)
add_subdirectory(log)
add_subdirectory(tcp)
add_subdirectory(shmem)
add_subdirectory(net)