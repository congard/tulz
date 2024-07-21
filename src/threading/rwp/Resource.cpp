#include <tulz/threading/rwp/Resource.h>

#include <cassert>

namespace tulz::rwp {
Resource::Resource()
    : m_activeOp(OpType::None),
      m_activeCount(0),
      m_idCounter(0),
      m_upperUnlockBound(0) {}

void Resource::lockRead() {
    lock(OpType::Read);
}

void Resource::unlockRead() {
    unlock(OpType::Read);
}

void Resource::lockWrite() {
    lock(OpType::Write);
}

void Resource::unlockWrite() {
    unlock(OpType::Write);
}

void Resource::lock(OpType opType) {
    std::unique_lock lock {m_mutex};

    // if the queue is not empty, there is
    // at least one writer in the queue

    if (m_queue.empty() && (m_activeOp == OpType::None || (m_activeOp == opType && opType == OpType::Read))) {
        m_activeOp = opType;
    } else {
        auto id = m_idCounter++;

        enqueue(opType);

        m_cv.wait(lock, [id, this] {
            return id < m_upperUnlockBound;
        });
    }

    ++m_activeCount;
}

void Resource::unlock(OpType opType) {
    m_mutex.lock();

    assert(m_activeOp == opType);

    if (--m_activeCount == 0) {
        select();
        m_mutex.unlock();
        m_cv.notify_all();
    } else {
        m_mutex.unlock();
    }
}

void Resource::enqueue(OpType opType) {
    if (m_queue.empty() || opType == OpType::Write) {
        m_queue.push_back({.type = opType, .upperBound = m_idCounter});
    } else {
        // non-empty queue, read op
        if (auto &op = m_queue.back(); op.type == OpType::Read) {
            op.upperBound = m_idCounter;
        } else {
            m_queue.push_back({.type = OpType::Read, .upperBound = m_idCounter});
        }
    }
}

void Resource::select() {
    // `select()` is called when the resource is fully unlocked.
    // So if the queue is empty, we can reset the resource
    // to the initial state
    if (m_queue.empty()) {
        m_activeOp = OpType::None;
        m_idCounter = 0;
        m_upperUnlockBound = 0;
        return;
    }

    auto op = m_queue.front();
    m_queue.pop_front();

    m_activeOp = op.type;
    m_upperUnlockBound = op.upperBound;
}
} // tulz::rwp