add_library(log STATIC log.cpp
                       Logger.cpp)

target_include_directories(log PUBLIC ${PROJECT_SOURCE_DIR}/include)