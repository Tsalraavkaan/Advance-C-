add_library(shmem STATIC Semaphore.cpp
                         SemLock.cpp)
target_include_directories(shmem PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(shmem PUBLIC ${CMAKE_SOURCE_DIR}/exceptions/include)