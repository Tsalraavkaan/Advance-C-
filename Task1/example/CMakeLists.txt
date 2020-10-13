add_executable(test_task1 parent.cpp)
add_executable(func child.cpp)
target_link_libraries(test_task1 Process)
target_link_libraries(test_task1 Descriptor)
