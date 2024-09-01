#include <gtest/gtest.h>

#include <tulz/observer/Observable.h>

#include <utility>

using namespace tulz;

TEST(ObservableTest, Int) {
    int currentValue {0};
    Observable<int> observable {currentValue};
    size_t counter {0};

    observable.subscribe([&](int value) {
        ++counter;
        currentValue = value;
    });

    observable = 5;

    ASSERT_EQ(currentValue, 5);
    ASSERT_EQ(counter, 1);

    ASSERT_EQ(++observable, 6);

    ASSERT_EQ(currentValue, 6);
    ASSERT_EQ(counter, 2);

    // subscribers will not be notified: value hasn't been changed
    observable = 6;
    observable += 0;

    ASSERT_EQ(counter, 2);

    // subscribers will be notified since the value has been changed
    observable += 4;

    ASSERT_EQ(currentValue, 10);
    ASSERT_EQ(counter, 3);
}

TEST(ObservableTest, FloatNearEq) {
    constexpr float precision {0.01f};

    auto nearEqEpsilonCmp = [](float epsilon, float f1, float f2) {
        return std::abs(f1 - f2) < epsilon;
    };

    auto eq = std::bind_front(nearEqEpsilonCmp, precision);

    float initialValue {0.33f};
    float currentValue{initialValue};
    size_t counter {0};

    Observable<float, decltype(eq)> observable{ currentValue, std::move(eq) };

    observable.subscribe([&](float value) {
        ++counter;
        currentValue = value;
    });

    observable = 1.0f / 3.0f;

    // subscribers will not be notified:
    // because of custom comparator, values considered equal
    ASSERT_EQ(counter, 0);

    // value will not be overwritten
    ASSERT_EQ(initialValue, observable.value());

    observable = 3.14f;

    ASSERT_EQ(currentValue, 3.14f);
    ASSERT_EQ(counter, 1);
}

TEST(ObservableTest, String) {
    using namespace std::string_view_literals;

    std::string currentValue {"foo"};
    size_t counter {0};

    Observable<std::string> observable {currentValue};

    observable.subscribe([&](std::string value) {
        ++counter;
        currentValue = std::move(value);
    });

    observable += " bar"sv;

    ASSERT_EQ(currentValue, "foo bar");
    ASSERT_EQ(counter, 1);

    observable = "baz";

    ASSERT_EQ(currentValue, "baz");
    ASSERT_EQ(counter, 2);

    observable += ""sv;

    ASSERT_EQ(counter, 2);
}