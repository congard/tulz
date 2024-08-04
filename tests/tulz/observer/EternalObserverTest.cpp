#include <gtest/gtest.h>

#include <tulz/observer/Subject.h>
#include <tulz/observer/EternalObserver.h>
#include <tulz/observer/EternalObserverFactory.h>

using namespace tulz;

TEST(EternalObserverTest, SelfInvalidate) {
    Subject<> subject;
    int counter {0};

    using Self = EternalObserver<>::SelfView;
    auto observer = EternalObserverFactory<>{}([&counter](Self self) {
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
