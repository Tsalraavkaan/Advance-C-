#include "Semaphore.hpp"

namespace Tasks {

namespace shmem {

Semaphore::Semaphore(int pshared) {
    if (::sem_init(&sem_id_, pshared, 1) < 0) {
        throw SemError("Error initializing semaphore");
    }
}

Semaphore::~Semaphore() {
    destroy();
}

void Semaphore::post() {
    if (::sem_post(&sem_id_) < 0) {
        throw SemError("Overflow in sem_post");
    }
}

void Semaphore::wait() {
    ::sem_wait(&sem_id_);
}

void Semaphore::destroy() {
    ::sem_destroy(&sem_id_);
}

} // namespace shmem

} //namespace Tasks
