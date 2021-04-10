#include <tulz/threading/Mutex.h>

namespace tulz {
void Mutex::lock() {
    m_mutex.lock();
}

void Mutex::tryLock() {
    m_mutex.try_lock();
}

void Mutex::unlock() {
    m_mutex.unlock();
}

std::mutex& Mutex::std_mutex() {
    return m_mutex;
}
}
