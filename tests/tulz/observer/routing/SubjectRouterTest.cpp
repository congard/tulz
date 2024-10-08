#include <gtest/gtest.h>

#include <tulz/observer/routing/SubjectRouter.h>
#include <tulz/observer/routing/ConcurrentSubjectRouter.h>
#include <tulz/observer/routing/RoutingKeyBuilder.h>

using namespace tulz;

using SubjectRouterTypes = testing::Types<SubjectRouter, ConcurrentSubjectRouter>;
template<typename T> struct SubjectRouterCommonTest : testing::Test {};

TYPED_TEST_SUITE(SubjectRouterCommonTest, SubjectRouterTypes);

TYPED_TEST(SubjectRouterCommonTest, SubscribeNotify) {
    TypeParam router;

    auto fooBarKey {RoutingKeyBuilder{"foo", "bar"}.build()};
    auto fooBazKey {RoutingKeyBuilder{"foo", "baz"}.build()};
    auto fooBazQuxKey {RoutingKeyBuilder{"foo", "baz", "qux"}.build()};
    auto fooAllKey {RoutingKeyBuilder{}.level("foo").all().build()};

    int fooBarCounter = 0;
    int fooBazCounter = 0;
    int fooBazQuxCounter = 0;

    router.subscribe(fooBarKey, [&]() {
        std::cout << "/foo/bar\n";
        ++fooBarCounter;
    });

    router.subscribe(fooBazKey, [&]() {
        std::cout << "/foo/baz\n";
        ++fooBazCounter;
    });

    router.template subscribe<const std::string&>(fooBazQuxKey, [&](const std::string &payload) {
        std::cout << "/foo/baz/qux, payload: " << payload << "\n";
        ++fooBazQuxCounter;
    });

    router.notify(fooBarKey);

    ASSERT_EQ(1, fooBarCounter);
    ASSERT_EQ(0, fooBazCounter);
    ASSERT_EQ(0, fooBazQuxCounter);

    router.notify(fooBazKey);

    ASSERT_EQ(1, fooBarCounter);
    ASSERT_EQ(1, fooBazCounter);
    ASSERT_EQ(0, fooBazQuxCounter);

    router.notify(fooAllKey);

    ASSERT_EQ(2, fooBarCounter);
    ASSERT_EQ(2, fooBazCounter);
    ASSERT_EQ(0, fooBazQuxCounter);

    router.template notify<const std::string&>(fooBazQuxKey, "Hello, qux!");

    ASSERT_EQ(2, fooBarCounter);
    ASSERT_EQ(2, fooBazCounter);
    ASSERT_EQ(1, fooBazQuxCounter);
}

TYPED_TEST(SubjectRouterCommonTest, Exists) {
    TypeParam router;

    auto fooBarKey {RoutingKeyBuilder{"foo", "bar"}.build()};
    auto fooBazKey {RoutingKeyBuilder{"foo", "baz"}.build()};
    auto fooBazQuxKey {RoutingKeyBuilder{"foo", "baz", "qux"}.build()};

    router.subscribe(fooBarKey, []() {});
    router.subscribe(fooBazKey, []() {});
    router.subscribe(fooBazQuxKey, []() {});

    ASSERT_TRUE(router.exists(fooBarKey));
    ASSERT_TRUE(router.exists(fooBazKey));
    ASSERT_TRUE(router.exists(fooBazQuxKey));

    ASSERT_TRUE(router.exists(RoutingKeyBuilder {}.level("foo").all().build()));
    ASSERT_TRUE(router.exists(RoutingKeyBuilder {"foo", std::regex {"ba[rz]"}}.build()));
    ASSERT_TRUE(router.exists(RoutingKeyBuilder {"foo", std::regex {"baz"}, "qux"}.build()));
    ASSERT_TRUE(router.exists(RoutingKeyBuilder {"foo", std::regex {"ba[rz]"}, "qux"}.build()));

    ASSERT_FALSE(router.exists(RoutingKeyBuilder {"foo", "bar", "qux"}.build()));
}

TYPED_TEST(SubjectRouterCommonTest, Shrink) {
    TypeParam router;

    auto fooKey {RoutingKeyBuilder{"foo"}.build()};
    auto fooBarKey {RoutingKeyBuilder{"foo", "bar"}.build()};
    auto fooBazKey {RoutingKeyBuilder{"foo", "baz"}.build()};
    auto fooBarQuxKey {RoutingKeyBuilder{"foo", "bar", "qux"}.build()};
    auto fooBazQuxKey {RoutingKeyBuilder{"foo", "baz", "qux"}.build()};
    auto tripleAllKey {RoutingKeyBuilder{}.all().all().all().build()};

    USubscription fooBarSub {router.subscribe(fooBarKey, [] {})};
    USubscription fooBazSub {router.subscribe(fooBazKey, [] {})};
    USubscription fooBarQuxSub {router.subscribe(fooBarQuxKey, [] {})};
    USubscription fooBazQuxSub {router.subscribe(fooBazQuxKey, [] {})};

    /*
     * /
     *   foo
     *     bar
     *       qux
     *     baz
     *       qux
     */

    router.shrink(tripleAllKey);

    ASSERT_TRUE(router.exists(fooBarKey));
    ASSERT_TRUE(router.exists(fooBazKey));
    ASSERT_TRUE(router.exists(fooBarQuxKey));
    ASSERT_TRUE(router.exists(fooBazQuxKey));

    fooBarSub->unsubscribe();
    router.shrink(tripleAllKey);

    // /foo/bar/qux still exists

    ASSERT_TRUE(router.exists(fooBarKey));
    ASSERT_TRUE(router.exists(fooBazKey));
    ASSERT_TRUE(router.exists(fooBarQuxKey));
    ASSERT_TRUE(router.exists(fooBazQuxKey));

    fooBarQuxSub->unsubscribe();
    router.shrink(tripleAllKey);

    // /foo/bar has been also removed

    ASSERT_FALSE(router.exists(fooBarKey));
    ASSERT_TRUE(router.exists(fooBazKey));
    ASSERT_FALSE(router.exists(fooBarQuxKey));
    ASSERT_TRUE(router.exists(fooBazQuxKey));

    fooBazSub->unsubscribe();
    fooBazQuxSub->unsubscribe();
    router.shrink(tripleAllKey);

    // /foo has been also removed

    ASSERT_FALSE(router.exists(fooKey));
    ASSERT_FALSE(router.exists(fooBazKey));
    ASSERT_FALSE(router.exists(fooBazQuxKey));
}

TYPED_TEST(SubjectRouterCommonTest, Depth) {
    TypeParam router;

    auto fooBarKey {RoutingKeyBuilder{"foo", "bar"}.build()};
    auto fooBazKey {RoutingKeyBuilder{"foo", "baz"}.build()};
    auto fooBazQuxKey {RoutingKeyBuilder{"foo", "baz", "qux"}.build()};

    router.subscribe(fooBarKey, []() {});
    router.subscribe(fooBazKey, []() {});
    router.subscribe(fooBazQuxKey, []() {});

    // 3 + <root>
    ASSERT_EQ(4, router.depth());
}
