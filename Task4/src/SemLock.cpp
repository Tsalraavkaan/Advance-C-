#include "SemLock.hpp"

namespace Tasks {

SemLock::SemLock(Semaphore &copy_sem) : sem{copy_sem} {
    sem.wait();
}

SemLock::~SemLock() {
    sem.post();
}

} //namespace Tasks