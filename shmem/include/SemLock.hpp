#ifndef PROJECT_SEMLOCK
#define PROJECT_SEMLOCK

#include "Semaphore.hpp"

namespace Project {

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

} //namespace Project

#endif