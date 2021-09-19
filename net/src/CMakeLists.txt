add_library(net STATIC BufConnection.cpp
                       EPoll.cpp
                       Service.cpp)
target_include_directories(net PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(proc PUBLIC ${CMAKE_SOURCE_DIR}/exceptions/include)
target_include_directories(proc PUBLIC ${CMAKE_SOURCE_DIR}/net/include)

target_link_libraries(net tcp)
