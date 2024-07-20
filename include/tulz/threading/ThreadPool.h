#ifndef SPACE_EXPLORER_THREADPOOL_H
#define SPACE_EXPLORER_THREADPOOL_H

#include <condition_variable>
#include <mutex>
#include <type_traits>
#include <list>

#include "Runnable.h"

namespace tulz {
class Thread;

class TULZ_API ThreadPool {
    friend class PooledRunnable;

public:
    ThreadPool();

    template<typename T, typename ...Args>
    std::enable_if_t<!Runnable::isRunnable<T>::value, void>
    start(T ptr, Args&&... args) {
        start(new TRunnable<T, Args...>(ptr, std::forward<Args>(args)...));
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
    std::mutex m_poolMutex;
    std::mutex m_queueMutex;

private:
    template<typename T, typename ...Args>
    class TRunnable: public Runnable {
    public:
        explicit TRunnable(T ptr, Args&&... args)
            : m_ptr(ptr),
              m_args(std::forward<Args>(args)...) {}

        void run() override {
            invoke(std::index_sequence_for<Args...>());
        }

    private:
        template<size_t... I>
        constexpr void invoke(std::index_sequence<I...>) {
            m_ptr(std::get<I>(m_args)...);
        }

    private:
        T m_ptr;
        std::tuple<Args...> m_args;
    };
};
}

#endif //SPACE_EXPLORER_THREADPOOL_H
