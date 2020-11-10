#include "SemLock.hpp"

namespace Tasks {

namespace shmem {

SemLock::SemLock(Semaphore &copy_sem) : sem{copy_sem} {
    sem.wait();
}

SemLock::~SemLock() {
    sem.post();
}

} // namespace shmem

} //namespace Tasks