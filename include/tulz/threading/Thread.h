#ifndef SPACE_EXPLORER_THREAD_H
#define SPACE_EXPLORER_THREAD_H

#include <thread>

#include "Runnable.h"

namespace tulz {
class Thread {
public:
    Thread() = default;

    template<typename T>
    explicit Thread(T ptr) {
        start(ptr);
    }

    template<typename T>
    typename std::enable_if_t<!Runnable::isRunnable<T>::value, void> start(T ptr) {
        m_thread = std::thread([&]() {
            ptr();
            m_isFinished = true;
        });
    }

    void start(Runnable *runnable);

    void join();

    bool isJoinable() const;
    bool isFinished() const;
    bool isRunning() const;

    std::thread& std_thread();

    static void sleep(long ms);

    template<class Rep, class Period>
    static void sleep(const std::chrono::duration<Rep, Period> &sleep_duration) {
        std::this_thread::sleep_for(sleep_duration);
    }

private:
    std::thread m_thread;
    bool m_isFinished = false;
};
}

#endif //SPACE_EXPLORER_THREAD_H
