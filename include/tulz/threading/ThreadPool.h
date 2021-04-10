#ifndef SPACE_EXPLORER_THREADPOOL_H
#define SPACE_EXPLORER_THREADPOOL_H

#include <condition_variable>
#include <type_traits>
#include <list>

#include "Mutex.h"
#include "Runnable.h"

namespace tulz {
class Thread;

class ThreadPool {
    friend class PooledRunnable;

public:
    ThreadPool();

    template<typename T>
    typename std::enable_if_t<!Runnable::isRunnable<T>::value, void> start(T ptr) {
        start(new TRunnable<T>(ptr));
    }

    void start(Runnable *runnable);
    void clear();
    void stop();
    void update();

    void setExpiryTimeout(int expiryTimeout);
    void setMaxThreadCount(int maxThreadCount);

    int getExpiryTimeout() const;
    int getMaxThreadCount() const;
    int getActiveThreadCount() const;
    int getThreadCount() const;

    bool isRunning() const;

private:
    std::list<Thread*> m_pool;
    std::list<Runnable*> m_queue;
    std::condition_variable m_condition;

private:
    int m_expiryTimeout;
    int m_maxThreadCount;
    bool m_isRunning;

private:
    Mutex m_poolMutex;
    Mutex m_queueMutex;

private:
    template<typename T>
    class TRunnable: public Runnable {
    public:
        explicit TRunnable(T ptr)
            : m_ptr(ptr) {}

        void run() override {
            m_ptr();
        }

    private:
        T m_ptr;
    };
};
}

#endif //SPACE_EXPLORER_THREADPOOL_H
