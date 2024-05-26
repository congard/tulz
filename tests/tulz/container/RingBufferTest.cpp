#include "tulz/container/RingBuffer.h"

#include <string>
#include <gtest/gtest.h>

TEST(RingBufferTest, InitializerList) {
    tulz::RingBuffer<int> buffer {1, 2, 3, 4};
    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());
    EXPECT_EQ(1, buffer[0]);
    EXPECT_EQ(2, buffer[1]);
    EXPECT_EQ(3, buffer[2]);
    EXPECT_EQ(4, buffer[3]);
}

TEST(RingBufferTest, Iterator) {
    tulz::RingBuffer<int> buffer {1, 2, 3, 4};
    int i = 0;

    for (int j : buffer) {
        ++i;
        EXPECT_EQ(i, j);
    }
}

TEST(RingBufferTest, IntBackInsertions) {
    tulz::RingBuffer<int> buffer(4);

    EXPECT_EQ(1, buffer.push_back(1));
    EXPECT_EQ(2, buffer.push_back(2));
    EXPECT_EQ(3, buffer.emplace_back(3));
    EXPECT_EQ(4, buffer.emplace_back(4));

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<int> expected {1, 2, 3, 4};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, IntFrontInsertions) {
    tulz::RingBuffer<int> buffer(4);

    EXPECT_EQ(1, buffer.push_front(1));
    EXPECT_EQ(2, buffer.push_front(2));
    EXPECT_EQ(3, buffer.emplace_front(3));
    EXPECT_EQ(4, buffer.emplace_front(4));

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<int> expected {4, 3, 2, 1};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, IntOverwrite) {
    tulz::RingBuffer<int, true> buffer(4);

#define EMPLACE_BACK_CHECKED(n) EXPECT_EQ(n, buffer.emplace_back(n))
#define EMPLACE_FRONT_CHECKED(n) EXPECT_EQ(n, buffer.emplace_front(n))

    EMPLACE_BACK_CHECKED(1);
    EMPLACE_BACK_CHECKED(2);
    EMPLACE_BACK_CHECKED(3);
    EMPLACE_BACK_CHECKED(4);
    EMPLACE_BACK_CHECKED(5);
    EMPLACE_BACK_CHECKED(6);
    EMPLACE_FRONT_CHECKED(7);

#undef EMPLACE_FRONT_CHECKED
#undef EMPLACE_BACK_CHECKED

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<int> expected {7, 3, 4, 5};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, IntPop) {
    tulz::RingBuffer<int> buffer(4);
    buffer.emplace_back(1);
    buffer.emplace_back(2);
    buffer.emplace_back(3);
    buffer.emplace_back(4);

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    EXPECT_EQ(1, buffer.pop_front());
    EXPECT_EQ(3, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    EXPECT_EQ(4, buffer.pop_back());
    EXPECT_EQ(2, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<int> expected {2, 3};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, IntResize) {
    tulz::RingBuffer<int> buffer {1, 2};

    EXPECT_EQ(2, buffer.size());
    EXPECT_EQ(2, buffer.capacity());

    buffer.resize(4);

    EXPECT_EQ(2, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    buffer.emplace_back(3);
    buffer.emplace_back(4);

    {
        tulz::RingBuffer<int> expected {1, 2, 3, 4};
        EXPECT_EQ(expected, buffer);
    }

    buffer.resize(2);

    EXPECT_EQ(2, buffer.size());
    EXPECT_EQ(2, buffer.capacity());

    {
        tulz::RingBuffer<int> expected {1, 2};
        EXPECT_EQ(expected, buffer);
    }
}

TEST(RingBufferTest, IntPartsResize) {
    tulz::RingBuffer<int> buffer {1, 2, 3, 4, 5};

    // prepare data

    EXPECT_EQ(1, buffer.pop_front());
    EXPECT_EQ(2, buffer.pop_front());
    EXPECT_EQ(3, buffer.pop_front());
    EXPECT_EQ(4, buffer.pop_front());

    buffer.emplace_back(6);
    buffer.emplace_back(7);

    {
        tulz::RingBuffer<int> expected {5, 6, 7};
        EXPECT_EQ(expected, buffer);
        EXPECT_EQ(3, buffer.size());
        EXPECT_EQ(5, buffer.capacity());
    }

    // now, the buffer should have the following internal layout:
    // {6, 7, x, x, 5}

    {
        // test 1: shrink
        auto testBuffer = buffer;
        testBuffer.resize(4);

        tulz::RingBuffer<int> expected {5, 6, 7};

        EXPECT_EQ(expected, testBuffer);
        EXPECT_EQ(3, testBuffer.size());
        EXPECT_EQ(4, testBuffer.capacity());
    }

    {
        // test 2: grow
        auto testBuffer = buffer;
        testBuffer.resize(6);

        tulz::RingBuffer<int> expected {5, 6, 7};

        EXPECT_EQ(expected, testBuffer);
        EXPECT_EQ(3, testBuffer.size());
        EXPECT_EQ(6, testBuffer.capacity());
    }
}

TEST(RingBufferTest, StringBackInsertions) {
    tulz::RingBuffer<std::string> buffer(4);
    buffer.push_back("foo");
    buffer.push_back("bar");
    buffer.emplace_back("baz");
    buffer.emplace_back("qux");

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<std::string> expected {"foo", "bar", "baz", "qux"};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, StringFrontInsertions) {
    tulz::RingBuffer<std::string> buffer(4);
    buffer.push_front("foo");
    buffer.push_front("bar");
    buffer.emplace_front("baz");
    buffer.emplace_front("qux");

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<std::string> expected {"qux", "baz", "bar", "foo"};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, StringOverwrite) {
    tulz::RingBuffer<std::string, true> buffer(4);
    buffer.emplace_back("a");
    buffer.emplace_back("b");
    buffer.emplace_back("c");
    buffer.emplace_back("d");
    buffer.emplace_back("e");
    buffer.emplace_back("f");
    buffer.emplace_front("g");

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<std::string> expected {"g", "c", "d", "e"};

    EXPECT_EQ(expected, buffer);
}

TEST(RingBufferTest, StringPop) {
    tulz::RingBuffer<std::string> buffer(4);
    buffer.emplace_back("foo");
    buffer.emplace_back("bar");
    buffer.emplace_back("baz");
    buffer.emplace_back("qux");

    EXPECT_EQ(4, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    EXPECT_EQ("foo", buffer.pop_front());
    EXPECT_EQ(3, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    EXPECT_EQ("qux", buffer.pop_back());
    EXPECT_EQ(2, buffer.size());
    EXPECT_EQ(4, buffer.capacity());

    tulz::RingBuffer<std::string> expected {"bar", "baz"};

    EXPECT_EQ(expected, buffer);
}
