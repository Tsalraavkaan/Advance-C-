#ifndef TASKS_SEMLOCK_H
#define TASKS_SEMLOCK_H

#include "Semaphore.hpp"

namespace Tasks {

namespace shmem {

class SemLock {
public:
    Semaphore &sem;
    SemLock(Semaphore &);
    SemLock(const SemLock &) = delete;
    SemLock(SemLock &&) = delete;
    SemLock &operator=(const Semaphore &) = delete;
    SemLock &operator=(Semaphore &&) = delete;
    ~SemLock();
};

} // namespace shmem

} //namespace Tasks

#endif