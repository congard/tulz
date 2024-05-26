#include "tulz/container/RingBuffer.h"

#include <gtest/gtest.h>

struct Counters {
    size_t ctor {0};
    size_t dtor {0};
    size_t copy {0};
    size_t move {0};
};

struct Dummy {
    Counters *m_counters;

    explicit Dummy(Counters *counters)
        : m_counters(counters)
    {
        ++m_counters->ctor;
    }

    Dummy(const Dummy &other)
        : m_counters(other.m_counters)
    {
        ++m_counters->copy;
    }

    Dummy& operator=(const Dummy &other) {
        if (this == &other)
            return *this;

        m_counters = other.m_counters;
        ++m_counters->copy;

        return *this;
    }

    Dummy(Dummy &&other) noexcept
        : m_counters(other.m_counters)
    {
        ++m_counters->move;
    }

    Dummy& operator=(Dummy &&other) noexcept {
        if (this == &other)
            return *this;

        std::swap(m_counters, other.m_counters);
        ++m_counters->move;

        return *this;
    }

    ~Dummy() {
        ++m_counters->dtor;
    }
};

#define EXPECT_COUNTERS(...) { \
    Counters expected __VA_ARGS__; \
    EXPECT_EQ(expected.ctor, counters.ctor); \
    EXPECT_EQ(expected.dtor, counters.dtor); \
    EXPECT_EQ(expected.copy, counters.copy); \
    EXPECT_EQ(expected.move, counters.move); \
}

TEST(RingBufferEfficiencyTest, PushAndEmplace) {
    Counters counters;

    {
        tulz::RingBuffer<Dummy> buffer(4);
        buffer.push_back(Dummy{&counters});
        buffer.push_front(Dummy{&counters});
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);
    }

    EXPECT_COUNTERS({.ctor = 4, .dtor = 6, .copy = 2})
}

TEST(RingBufferEfficiencyTest, OverwriteAndPop) {
    Counters counters;

    {
        tulz::RingBuffer<Dummy> buffer(4);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);

        EXPECT_COUNTERS({.ctor = 4})

        {
            buffer.pop_back();
        }

        EXPECT_COUNTERS({.ctor = 4, .dtor = 1, .move = 1})

        {
            buffer.pop_front();
        }

        EXPECT_COUNTERS({.ctor = 4, .dtor = 2, .move = 2})
    }

    EXPECT_COUNTERS({.ctor = 4, .dtor = 4, .move = 2})
}

TEST(RingBufferEfficiencyTest, Resize) {
    Counters counters;

    {
        tulz::RingBuffer<Dummy> buffer(4);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);

        EXPECT_COUNTERS({.ctor = 4})

        buffer.resize(6);

        EXPECT_COUNTERS({.ctor = 4})

        buffer.resize(2);

        EXPECT_COUNTERS({.ctor = 4, .dtor = 2})
    }

    EXPECT_COUNTERS({.ctor = 4, .dtor = 4})
}

TEST(RingBufferEfficiencyTest, ResizePartsShrink) {
    Counters counters;

    {
        tulz::RingBuffer<Dummy> buffer(4);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);

        EXPECT_COUNTERS({.ctor = 4})

        {
            buffer.pop_front();
            buffer.pop_front();
            buffer.pop_front();
        }

        EXPECT_COUNTERS({.ctor = 4, .dtor = 3, .move = 3})

        buffer.emplace_back(&counters);
        buffer.emplace_back(&counters);

        EXPECT_COUNTERS({.ctor = 6, .dtor = 3, .move = 3})

        // now, the buffer should have the following internal layout:
        // {B, C, x, A}

        buffer.resize(2);

        // {A, B}

        EXPECT_COUNTERS({.ctor = 6, .dtor = 4, .move = 3})
    }

    EXPECT_COUNTERS({.ctor = 6, .dtor = 6, .move = 3})
}

TEST(RingBufferEfficiencyTest, ResizePartsGrow) {
    Counters counters;

    {
        tulz::RingBuffer<Dummy> buffer(4);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);
        buffer.emplace_back(&counters);
        buffer.emplace_front(&counters);

        EXPECT_COUNTERS({.ctor = 4})

        {
            buffer.pop_front();
            buffer.pop_front();
            buffer.pop_front();
        }

        EXPECT_COUNTERS({.ctor = 4, .dtor = 3, .move = 3})

        buffer.emplace_back(&counters);
        buffer.emplace_back(&counters);

        EXPECT_COUNTERS({.ctor = 6, .dtor = 3, .move = 3})

        // now, the buffer should have the following internal layout:
        // {B, C, x, A}

        buffer.resize(6);

        // {A, B, C, x, x, x}

        EXPECT_COUNTERS({.ctor = 6, .dtor = 3, .move = 3})
    }

    EXPECT_COUNTERS({.ctor = 6, .dtor = 6, .move = 3})
}
