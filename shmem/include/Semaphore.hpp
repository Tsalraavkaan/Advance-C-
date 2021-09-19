#ifndef PROJECT_SEMAPHORE
#define PROJECT_SEMAPHORE

#include <semaphore.h>
#include "Exceptions.hpp"

namespace Project {

namespace shmem {

class Semaphore {
private:
    sem_t sem_id_;
public:
    Semaphore(int = 1);
    ~Semaphore();
    void post();
    void wait();
    void destroy();
};

} // namespace shmem

} //namespace Project

#endif