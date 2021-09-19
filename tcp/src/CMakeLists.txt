add_library(tcp STATIC Socket.cpp
                       Connection.cpp
                       Server.cpp)
target_include_directories(tcp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(tcp PUBLIC ${CMAKE_SOURCE_DIR}/exceptions/include)
target_include_directories(tcp PUBLIC ${CMAKE_SOURCE_DIR}/descriptor/include)

target_link_libraries(tcp desc)