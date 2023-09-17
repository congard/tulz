#include <tulz/Array.h>
#include <gtest/gtest.h>

TEST(ArrayTest, InitializerList) {
    tulz::Array<int> array {0, 1, 2, 3};
    EXPECT_TRUE(array.size() == 4);

    for (int i = 0; i < array.size(); ++i) {
        EXPECT_TRUE(array[i] == i);
    }
}

TEST(ArrayTest, InitWithValue) {
    tulz::Array<int> array(5, 123);
    EXPECT_TRUE(array.size() == 5);

    for (int i: array) {
        EXPECT_TRUE(i == 123);
    }
}

TEST(ArrayTest, Iterator) {
    tulz::Array<int> array {0, 1, 2, 3};
    auto it = array.begin();

    EXPECT_TRUE(*it == 0);
    EXPECT_TRUE(*(++it) == 1);
    EXPECT_TRUE(*(++it) == 2);
    EXPECT_TRUE(*(++it) == 3);
    EXPECT_TRUE(*(--it) == 2);
}

TEST(ArrayTest, Distance) {
    tulz::Array<int> array(5);
    auto size = array.size();
    auto distance = std::distance(array.begin(), array.end());
    EXPECT_TRUE(size == distance);
}

TEST(ArrayTest, Classes) {
    tulz::Array<std::string> array(2);
    array[0] = std::string("foo");
    array[1] = std::string("bar");

    EXPECT_TRUE(array[0] == "foo");
    EXPECT_TRUE(array[1] == "bar");
}
