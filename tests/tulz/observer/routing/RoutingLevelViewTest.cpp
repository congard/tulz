#include <gtest/gtest.h>

#include <tulz/observer/routing/RoutingKeyBuilder.h>

using namespace tulz;

TEST(RoutingLevelViewTest, ConstructionByKey) {
    auto key = RoutingKeyBuilder {}
        .level("foo")
        .level("bar")
        .build();

    auto view = key.view();

    ASSERT_EQ(0, view.getLevelIndex());
    ASSERT_EQ(3, view.getLevelCount()); // 2 + 1 (root)
    ASSERT_EQ("", view.asString());
}

TEST(RoutingLevelViewTest, UpDownTest) {
    auto key = RoutingKeyBuilder {}
        .level("foo")
        .level("bar")
        .build();

    auto view0 = key.view();
    ASSERT_TRUE(view0.isRoot());
    ASSERT_FALSE(view0.isLeaf());
    ASSERT_EQ(0, view0.getLevelIndex());
    ASSERT_EQ("", view0.asString());

    auto view1 = view0.up();
    ASSERT_FALSE(view1.isRoot());
    ASSERT_FALSE(view1.isLeaf());
    ASSERT_EQ(1, view1.getLevelIndex());
    ASSERT_EQ("foo", view1.asString());

    auto view2 = view1.up();
    ASSERT_FALSE(view2.isRoot());
    ASSERT_TRUE(view2.isLeaf());
    ASSERT_EQ(2, view2.getLevelIndex());
    ASSERT_EQ("bar", view2.asString());

    auto view3 = view2.down();
    ASSERT_EQ(1, view3.getLevelIndex());
    ASSERT_EQ("foo", view3.asString());
}

TEST(RoutingLevelViewTest, MatchesTest) {
    auto key = RoutingKeyBuilder {}
        .level("foo")
        .level(std::regex("bar|baz"))
        .all()
        .level("qux")
        .build();

    auto view0 = key.view();
    ASSERT_TRUE(view0.matches(""));
    ASSERT_FALSE(view0.matches("foo"));

    auto view1 = view0.up();
    ASSERT_TRUE(view1.matches("foo"));

    auto view2 = view1.up();
    ASSERT_FALSE(view2.matches("foo"));
    ASSERT_TRUE(view2.matches("bar"));
    ASSERT_TRUE(view2.matches("baz"));

    auto view3 = view2.up();
    ASSERT_TRUE(view3.matches(""));
    ASSERT_TRUE(view3.matches("qwerty"));
    ASSERT_TRUE(view3.matches("asdf12"));
    ASSERT_TRUE(view3.matches("q+?iOp(0.>QS"));

    auto view4 = view3.up();
    ASSERT_FALSE(view4.matches("baz"));
    ASSERT_TRUE(view4.matches("qux"));
}