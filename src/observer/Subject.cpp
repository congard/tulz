#include <tulz/observer/Subject.h>
#include <stdexcept>

namespace tulz {
Subject::Subject()
    : m_lastObserverIt(m_observers.before_begin()) {}

Subscription Subject::subscribe(const Observer &observer) {
    auto &inserted = *m_observers.insert_after(m_lastObserverIt, observer);
    ++m_lastObserverIt;
    return {this, &inserted};
}

void Subject::unsubscribe(Subscription &subscription) {
    if (!subscription.isValid())
        throw std::invalid_argument("Invalid subscription");

    if (this != subscription.m_subject)
        throw std::runtime_error("Cannot unsubscribe subscription that doesn't belong to this subject");

    m_observers.remove_if([&subscription](const Observer &observer) {
        return &observer == subscription.m_observer;
    });

    m_lastObserverIt = m_observers.before_begin();
    for (auto it = m_observers.begin(); it != m_observers.end(); m_lastObserverIt = it++);

    subscription.m_subject = nullptr;
    subscription.m_observer = nullptr;
}

void Subject::notify() {
    for (auto &observer : m_observers) {
        observer();
    }
}
}
