#ifndef TASKS_SEMLOCK_H
#define TASKS_SEMLOCK_H

#include "Semaphore.hpp"

namespace Tasks {

class SemLock {
public:
    Semaphore &sem;
    SemLock(Semaphore &);
    ~SemLock();
};

} //namespace Tasks

#endif