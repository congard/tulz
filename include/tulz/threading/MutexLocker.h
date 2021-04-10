#ifndef SPACE_EXPLORER_MUTEXLOCKER_H
#define SPACE_EXPLORER_MUTEXLOCKER_H

#include "Mutex.h"

namespace tulz {
class MutexLocker {
public:
    explicit MutexLocker(Mutex &mutex);

    std::unique_lock<std::mutex>& std_locker();

private:
    std::unique_lock<std::mutex> m_locker;
};
}

#endif //SPACE_EXPLORER_MUTEXLOCKER_H
