#include <tulz/threading/ThreadPool.h>
#include <tulz/threading/Thread.h>

#include <chrono>

namespace tulz {
inline static auto time() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

class PooledThread: public Thread {
public:
    PooledThread()
        : m_lastActiveTime(time()) {}

    void setLastActiveTime(int64_t time) {
        m_lastActiveTime = time;
    }

    auto getLastActiveTime() const {
        return m_lastActiveTime;
    }

private:
    int64_t m_lastActiveTime;
};

class PooledRunnable: public Runnable {
public:
    explicit PooledRunnable(ThreadPool *pool, PooledThread *pooledThread)
        : m_threadPool(pool),
          m_pooledThread(pooledThread) {}

    void run() override;

private:
    ThreadPool *m_threadPool;
    PooledThread *m_pooledThread;
};

void PooledRunnable::run() {
    while (true) {
        Runnable *runnable;

        {
            std::unique_lock locker(m_threadPool->m_queueMutex);

            auto &queue = m_threadPool->m_queue;

            bool isExpired;

            m_threadPool->m_condition.wait(locker, [&]() {
                auto passedTime = time() - m_pooledThread->getLastActiveTime();
                auto expiryTimeout = m_threadPool->getExpiryTimeout();

                isExpired = (expiryTimeout >= 0) && (passedTime > expiryTimeout);

                return !queue.empty() || !m_threadPool->isRunning() || isExpired;
            });

            if (!m_threadPool->isRunning())
                return;

            if (queue.empty() && isExpired)
                return;

            auto qFront = queue.begin();
            runnable = *qFront;
            queue.erase(qFront);
        }

        runnable->run();

        m_pooledThread->setLastActiveTime(time());

        delete runnable;
    }
}

ThreadPool::ThreadPool()
    : m_maxThreadCount(4),
      m_expiryTimeout(30000),
      m_isRunning(true) {}

void ThreadPool::start(Runnable *runnable) {
    if (!m_isRunning) {
        m_isRunning = true;
    }

    {
        std::scoped_lock locker(m_queueMutex);
        m_queue.emplace_back(runnable);
    }

    {
        std::scoped_lock locker(m_poolMutex);

        if ((m_maxThreadCount > m_pool.size() || m_maxThreadCount < 0) && getActiveThreadCount() == getThreadCount())
        {
            auto pooledThread = new PooledThread();
            pooledThread->start(new PooledRunnable(this, pooledThread));
            m_pool.emplace_back(pooledThread);
        }
    }

    m_condition.notify_one();
}

void ThreadPool::clear() {
    std::scoped_lock locker(m_queueMutex);

    for (auto runnable : m_queue) {
        delete runnable;
    }

    m_queue.clear();
}

void ThreadPool::stop() {
    m_isRunning = false;
    m_condition.notify_all();

    {
        std::scoped_lock locker(m_poolMutex);

        for (auto thread : m_pool) {
            thread->join();
            delete thread;
        }

        m_pool.clear();
    }

    clear();
}

void ThreadPool::update() {
    if (m_expiryTimeout < 0) {
        return;
    }

    m_condition.notify_all();

    {
        std::scoped_lock locker(m_poolMutex);

        auto it = m_pool.begin();

        while (it != m_pool.end()) {
            auto thread = *it;

            if (thread->isFinished()) {
                thread->join();

                delete thread;

                it = m_pool.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void ThreadPool::setExpiryTimeout(int expiryTimeout) {
    m_expiryTimeout = expiryTimeout;
}

void ThreadPool::setMaxThreadCount(int maxThreadCount) {
    m_maxThreadCount = maxThreadCount;
}

int ThreadPool::getExpiryTimeout() const {
    return m_expiryTimeout;
}

int ThreadPool::getMaxThreadCount() const {
    return m_maxThreadCount;
}

int ThreadPool::getActiveThreadCount() const {
    int count = 0;

    for (auto thread : m_pool) {
        count += thread->isRunning();
    }

    return count;
}

int ThreadPool::getThreadCount() const {
    return m_pool.size();
}

bool ThreadPool::isRunning() const {
    return m_isRunning;
}
}
