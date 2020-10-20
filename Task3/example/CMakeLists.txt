add_executable(client client.cpp)
add_executable(server server.cpp)
target_link_libraries(client tcp)
target_link_libraries(server tcp)