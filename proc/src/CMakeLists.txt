add_library(proc STATIC Process.cpp)

target_include_directories(proc PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(proc PUBLIC ${CMAKE_SOURCE_DIR}/exceptions/include)
target_include_directories(proc PUBLIC ${CMAKE_SOURCE_DIR}/descriptor/include)
target_link_libraries(proc desc)