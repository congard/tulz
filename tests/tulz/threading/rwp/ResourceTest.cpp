#include <gtest/gtest.h>

#include <tulz/threading/rwp/Resource.h>
#include <tulz/threading/rwp/ReadLock.h>
#include <tulz/threading/rwp/WriteLock.h>

#include <thread>
#include <sstream>
#include <chrono>

using namespace tulz::rwp;

TEST(ResourceTest, SimultaneousRead) {
    Resource resource;
    resource.lockRead();
    resource.lockRead();
    resource.unlockRead();
    resource.unlockRead();
}

TEST(ResourceTest, SimulaneousReadBlockingWrite) {
    struct Action {
        enum class Type {
            Read, Write
        };

        Type type;
        long timestamp;
    };

    std::vector<Action> actions;
    std::mutex actionMutex;
    std::condition_variable actionCond;
    int actionCount {0};

    Resource resource;

    auto currentTimeMillis = [] {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    };

    auto appendAction = [&](Action action) {
        {
            std::lock_guard lock {actionMutex};
            actions.emplace_back(action);
            ++actionCount;
        }
        actionCond.notify_all();
    };

    auto waitForActionCount = [&](int count) {
        std::unique_lock lock {actionMutex};
        actionCond.wait(lock, [&] { return actionCount == count; });
    };

    auto reader = [&](long millisSleep) {
        ReadLock lock {resource};
        appendAction({.type = Action::Type::Read, .timestamp = currentTimeMillis()});
        std::this_thread::sleep_for(std::chrono::milliseconds {millisSleep});
    };

    auto writer = [&](long millisSleep) {
        WriteLock lock {resource};
        appendAction({.type = Action::Type::Write, .timestamp = currentTimeMillis()});
        std::this_thread::sleep_for(std::chrono::milliseconds {millisSleep});
    };

    auto startTime = currentTimeMillis();

    std::jthread r1 {reader, 500};
    std::jthread r2 {reader, 1000};

    waitForActionCount(2);

    std::jthread w1 {writer, 1000};
    std::jthread w2 {writer, 1000};

    waitForActionCount(4);

    std::jthread r3 {reader, 1000};
    std::jthread r4 {reader, 1000};

    waitForActionCount(6);

#define ASSERT_ACTION(index_, type_, expectedDelta_, deltaJitter_) \
    do { \
        ASSERT_EQ(actions[index_].type, type_); \
        auto delta = actions[index_].timestamp - startTime; \
        ASSERT_TRUE(expectedDelta_ <= delta && delta <= expectedDelta_ + deltaJitter_); \
    } while (false)

    // simultaneous read
    ASSERT_ACTION(0, Action::Type::Read, 0, 20);
    ASSERT_ACTION(1, Action::Type::Read, 0, 20);

    // sequential write
    ASSERT_ACTION(2, Action::Type::Write, 1000, 30);
    ASSERT_ACTION(3, Action::Type::Write, 2000, 30);

    // simultaneous read
    ASSERT_ACTION(4, Action::Type::Read, 3000, 40);
    ASSERT_ACTION(5, Action::Type::Read, 3000, 40);
}
