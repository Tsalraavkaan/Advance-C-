#ifndef TASKS_SEMAPHORE_H
#define TASKS_SEMAPHORE_H

#include <semaphore.h>
#include "Exceptions.hpp"

namespace Tasks {

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

} //namespace Tasks

#endif