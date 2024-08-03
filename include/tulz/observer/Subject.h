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
public:
    using Subscription_t = Subscription<Args_...>;
    using Observer_t = Observer<Args_...>;

public:
    Subject() = default;

    Subscription_t subscribe(const Observer_t &observer) {
        auto &details = m_observers.emplace_front(observer, m_subscriptionCounter++);
        m_activeSubscriptions.emplace(details.subscriptionId);
        return {details.subscriptionId, this, &details.observer};
    }

    void unsubscribe(Subscription_t &subscription) {
        if (!isSubscriptionValid(subscription))
            throw std::invalid_argument("Invalid subscription");

        m_observers.remove_if([&subscription](const ObserverDetails &details) {
            return details.subscriptionId == subscription.getId();
        });

        m_activeSubscriptions.erase(subscription.getId());

        subscription.m_id = InvalidSubscriptionId;
        subscription.m_subject = nullptr;
        subscription.m_observer = nullptr;
    }

    template<typename ...Args>
    void notify(Args&&... args) {
        struct CachedDetails {
            Observer_t *observer;
            SubscriptionId subscriptionId;
        };

        std::forward_list<CachedDetails> cachedDetails;

        for (auto &details : m_observers)
            cachedDetails.emplace_front(&details.observer, details.subscriptionId);

        for (auto [observer, subscriptionId] : cachedDetails) {
            if (isSubscriptionIdValid(subscriptionId)) {
                (*observer)(std::forward<Args>(args)...);
            }
        }
    }

    bool hasSubscriptions() const {
        return !m_observers.empty();
    }

    bool isSubscriptionValid(const Subscription_t &subscription) const {
        return subscription.m_subject == this && isSubscriptionIdValid(subscription.getId());
    }

private:
    bool isSubscriptionIdValid(SubscriptionId subscriptionId) const {
        return m_activeSubscriptions.find(subscriptionId) != m_activeSubscriptions.end();
    }

private:
    struct ObserverDetails {
        Observer_t observer;
        SubscriptionId subscriptionId;
    };

    std::forward_list<ObserverDetails> m_observers;
    std::set<SubscriptionId> m_activeSubscriptions;

    SubscriptionId m_subscriptionCounter {0};
};
}

#endif //TULZ_SUBJECT_H
