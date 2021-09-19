add_library(desc STATIC Descriptor.cpp)

target_include_directories(desc PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(desc PUBLIC ${CMAKE_SOURCE_DIR}/exceptions/include)