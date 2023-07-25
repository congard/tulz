#ifndef TULZ_SUBJECT_H
#define TULZ_SUBJECT_H

#include <forward_list>
#include <set>
#include <stdexcept>

#include "Observer.h"
#include "Subscription.h"

namespace tulz {
template<typename ...Args_>
class Subject {
    using Subscription_t = Subscription<Args_...>;
    using Observer_t = Observer<Args_...>;

public:
    Subject() = default;

    Subscription_t subscribe(const Observer_t &observer) {
        auto &inserted = m_observers.emplace_front(observer);
        m_observersSet.emplace(&inserted);
        return {this, &inserted};
    }

    void unsubscribe(Subscription_t &subscription) {
        if (!subscription.isValid())
            throw std::invalid_argument("Invalid subscription");

        if (this != subscription.m_subject)
            throw std::runtime_error("Cannot unsubscribe subscription that doesn't belong to this subject");

        m_observers.remove_if([&subscription](const Observer_t &observer) {
            return &observer == subscription.m_observer;
        });

        m_observersSet.erase(subscription.m_observer);

        subscription.m_subject = nullptr;
        subscription.m_observer = nullptr;
    }

    template<typename ...Args>
    void notify(Args&&... args) {
        std::forward_list<Observer_t*> observers;

        for (Observer_t &observer : m_observers)
            observers.emplace_front(&observer);

        for (Observer_t *observer : observers) {
            if (m_observersSet.find(observer) != m_observersSet.end()) {
                (*observer)(std::forward<Args>(args)...);
            }
        }
    }

private:
    std::forward_list<Observer_t> m_observers;
    std::set<Observer_t*> m_observersSet;
};
}

#endif //TULZ_SUBJECT_H
