link_libraries(shmem Threads::Threads)
add_executable(shmem_client client.cpp)