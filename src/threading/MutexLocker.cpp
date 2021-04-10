#include <tulz/threading/MutexLocker.h>

namespace tulz {
MutexLocker::MutexLocker(Mutex &mutex)
    : m_locker(mutex.std_mutex()) {}

std::unique_lock<std::mutex>& MutexLocker::std_locker() {
    return m_locker;
}
}
