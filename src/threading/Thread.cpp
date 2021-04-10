#include <tulz/threading/Thread.h>

namespace tulz {
void Thread::start(Runnable *runnable) {
    // we need to pass runnable as lambda argument
    // because otherwise we can get SIGBUS
    m_thread = std::thread([&](auto p) {
        p->run();
        delete p;

        m_isFinished = true;
    }, runnable);
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
    sleep(std::operator""ms(ms));
}
}
