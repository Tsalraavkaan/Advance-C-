add_executable(service test_service.cpp )
add_executable(client client.cpp)
target_link_libraries(service net)
target_link_libraries(client net)