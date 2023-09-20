#include <tulz/threading/Thread.h>

namespace tulz {
void Thread::start(Runnable *runnable) {
    m_thread = std::thread([this, runnable] {
        runnable->run();
        delete runnable;

        m_isFinished = true;
    });
}

void Thread::join() {
    m_thread.join();
}

bool Thread::isJoinable() const {
    return m_thread.joinable();
}

bool Thread::isFinished() const {
    return m_isFinished;
}

bool Thread::isRunning() const {
    return !m_isFinished;
}

std::thread& Thread::std_thread() {
    return m_thread;
}

void Thread::sleep(long ms) {
    sleep(std::chrono::duration<long double, std::milli> {ms});
}
}
