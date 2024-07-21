#ifndef TULZ_RESOURCE_H
#define TULZ_RESOURCE_H

#include <tulz/export.h>

#include <deque>
#include <mutex>
#include <condition_variable>

namespace tulz::rwp {
/**
 * Resource can be locked for reading and writing.
 *
 * - There can be multiple read locks at the same time,
 * - but only one write lock at any given moment.
 *
 * Fairness:
 * 1. if the queue is empty, readers will be allowed to
 *    acquire the resource immediately,
 * 2. if the queue is empty, only one writer will be allowed
 *    to acquire the resource at the same time,
 * 3. if the queue is non-empty or the resource is busy,
 *    lock requests will be added to the queue.
 */
class TULZ_API Resource {
public:
    Resource();

    void lockRead();
    void unlockRead();

    void lockWrite();
    void unlockWrite();

private:
    enum class OpType {
        None, Read, Write
    };

    using Id = int64_t;

    struct Operation {
        OpType type;
        Id upperBound;
    };

private:
    void lock(OpType opType);
    void unlock(OpType opType);

    void enqueue(OpType opType);
    void select();

private:
    std::deque<Operation> m_queue;
    OpType m_activeOp;
    size_t m_activeCount;
    Id m_idCounter;
    Id m_upperUnlockBound;

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
};
} // tulz::rwp

#endif //TULZ_RESOURCE_H
