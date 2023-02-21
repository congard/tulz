#include <tulz/observer/Subject.h>
#include <stdexcept>

namespace tulz {
Subject::Subject() = default;

Subscription Subject::subscribe(const Observer &observer) {
    auto &inserted = m_observers.emplace_front(observer);
    m_observersSet.emplace(&inserted);
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

    m_observersSet.erase(subscription.m_observer);

    subscription.m_subject = nullptr;
    subscription.m_observer = nullptr;
}

void Subject::notify() {
    std::forward_list<Observer*> observers;

    for (Observer &observer : m_observers)
        observers.emplace_front(&observer);

    for (Observer *observer : observers) {
        if (m_observersSet.find(observer) != m_observersSet.end()) {
            (*observer)();
        }
    }
}
}
