#ifndef SPACE_EXPLORER_MUTEX_H
#define SPACE_EXPLORER_MUTEX_H

#include <mutex>

namespace tulz {
class Mutex {
public:
    void lock();
    void tryLock();
    void unlock();

    std::mutex& std_mutex();

private:
    std::mutex m_mutex;
};
}

#endif //SPACE_EXPLORER_MUTEX_H
