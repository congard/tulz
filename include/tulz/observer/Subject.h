#ifndef TULZ_SUBJECT_H
#define TULZ_SUBJECT_H

#include <forward_list>
#include <set>
#include <stdexcept>

#include "Observer.h"
#include "ObserverAutoPtr.h"
#include "Subscription.h"

namespace tulz {
template<typename ...Args>
class Subject {
public:
    using Subscription_t = Subscription<Args...>;
    using Observer_t = Observer<Args...>;
    using ObserverPtr_t = ObserverPtr<Args...>;
    using ObserverAutoPtr_t = ObserverAutoPtr<Args...>;

public:
    Subject() = default;

    Subscription_t subscribe(ObserverAutoPtr_t observerAutoPtr) {
        auto &details = m_observers.emplace_front(*observerAutoPtr, m_subscriptionCounter++);
        m_activeSubscriptions.emplace(details.subscriptionId);
        return {details.subscriptionId, this, details.observer.get()};
    }

    void unsubscribe(Subscription_t &subscription) {
        if (!isSubscriptionValid(subscription))
            throw std::invalid_argument("Invalid subscription");

        unsubscribeById(subscription.getId());

        subscription.m_id = InvalidSubscriptionId;
        subscription.m_subject = nullptr;
        subscription.m_observer = nullptr;
    }

    void notify(Args... args) {
        struct CachedDetails {
            Observer_t *observer;
            SubscriptionId subscriptionId;
        };

        std::forward_list<CachedDetails> cachedDetails;

        for (auto &details : m_observers)
            cachedDetails.emplace_front(details.observer.get(), details.subscriptionId);

        for (auto [observer, subscriptionId] : cachedDetails) {
            if (isSubscriptionIdValid(subscriptionId)) {
                (*observer)(args...);

                if (!observer->isValid()) {
                    unsubscribeById(subscriptionId);
                }
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
        return m_activeSubscriptions.contains(subscriptionId);
    }

    void unsubscribeById(SubscriptionId subscriptionId) {
        m_observers.remove_if([subscriptionId](const ObserverDetails &details) {
            return details.subscriptionId == subscriptionId;
        });

        m_activeSubscriptions.erase(subscriptionId);
    }

private:
    struct ObserverDetails {
        ObserverPtr_t observer;
        SubscriptionId subscriptionId;
    };

    std::forward_list<ObserverDetails> m_observers;
    std::set<SubscriptionId> m_activeSubscriptions;

    SubscriptionId m_subscriptionCounter {0};
};
}

#endif //TULZ_SUBJECT_H
