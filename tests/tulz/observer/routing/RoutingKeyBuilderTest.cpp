#include <gtest/gtest.h>

#include <tulz/observer/routing/RoutingKeyBuilder.h>

using namespace tulz;

TEST(RoutingKeyBuilderTest, BasicBuilding) {
    auto key = RoutingKeyBuilder {}
        .level("foo")
        .level("bar")
        .build();

    ASSERT_EQ("", std::get<std::string>(key.getLevel(0))); // root node
    ASSERT_EQ("foo", std::get<std::string>(key.getLevel(1)));
    ASSERT_EQ("bar", std::get<std::string>(key.getLevel(2)));
}

TEST(RoutingKeyBuilderTest, ConstructorBuilding) {
    auto key = RoutingKeyBuilder {"foo", std::regex {"bar|baz"}}.build();

    ASSERT_EQ("", std::get<std::string>(key.getLevel(0))); // root node
    ASSERT_EQ("foo", std::get<std::string>(key.getLevel(1)));

    auto &l2Regex = std::get<std::regex>(key.getLevel(2));

    ASSERT_FALSE(std::regex_match("foo", l2Regex));
    ASSERT_TRUE(std::regex_match("bar", l2Regex));
    ASSERT_TRUE(std::regex_match("baz", l2Regex));
}

TEST(RoutingKeyBuilderTest, RegexBuilding) {
    auto key = RoutingKeyBuilder {}
        .level("foo")
        .level(std::regex {"bar|baz|qux"})
        .all()
        .build();

    ASSERT_EQ("", std::get<std::string>(key.getLevel(0))); // root node
    ASSERT_EQ("foo", std::get<std::string>(key.getLevel(1)));

    auto &l2Regex = std::get<std::regex>(key.getLevel(2));

    ASSERT_FALSE(std::regex_match("foo", l2Regex));
    ASSERT_TRUE(std::regex_match("bar", l2Regex));
    ASSERT_TRUE(std::regex_match("baz", l2Regex));
    ASSERT_TRUE(std::regex_match("qux", l2Regex));

    auto &l3Regex = std::get<std::regex>(key.getLevel(3));

    ASSERT_TRUE(std::regex_match("", l3Regex));
    ASSERT_TRUE(std::regex_match("qwerty", l3Regex));
    ASSERT_TRUE(std::regex_match("asdf*?", l3Regex));
    ASSERT_TRUE(std::regex_match("wasd12", l3Regex));
}
