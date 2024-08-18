#include <gtest/gtest.h>

#include <tulz/observer/Subject.h>
#include <tulz/observer/EternalObserver.h>
#include <tulz/observer/EternalObserverFactory.h>

using namespace tulz;

TEST(EternalObserverTest, SelfInvalidate) {
    Subject<> subject;
    int counter {0};

    using Observer = EternalObserver<>;
    auto observer = Observer::Factory{}([&counter](Observer::SelfView self) {
        ++counter;
        self->invalidate();
    });

    auto subscription = subject.subscribe(std::move(observer));

    ASSERT_TRUE(subscription.getObserver()->isValid());

    subject.notify();

    ASSERT_FALSE(subscription.isValid());

    subject.notify();

    ASSERT_EQ(counter, 1);
}

TEST(EternalObserverTest, ProducedByFactory) {
    Subject<int> subject;

    int value {0};

    using Observer = EternalObserver<int>;
    auto observer = Observer::Factory{}([&value](int i) {
        value = i;
    });

    auto subscription = subject.subscribe(std::move(observer));

    subject.notify(1);

    ASSERT_EQ(value, 1);

    subscription.unsubscribe();

    subject.notify(2);

    ASSERT_EQ(value, 1);
}
