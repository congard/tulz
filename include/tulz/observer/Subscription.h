#ifndef TULZ_SUBSCRIPTION_H
#define TULZ_SUBSCRIPTION_H

#include <limits>
#include <cstdint>

#include "Observer.h"

namespace tulz {
template<typename ...Args>
class Subject;

using SubscriptionId = uint32_t;
constexpr static auto InvalidSubscriptionId {std::numeric_limits<SubscriptionId>::max()};

template<typename ...Args>
class Subscription {
    friend class Subject<Args...>;

    using Subject_t = Subject<Args...>;
    using Observer_t = Observer<Args...>;

public:
    Subscription() = default;

    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;

    Subscription(Subscription &&rhs) noexcept {
        *this = std::move(rhs);
    }

    Subscription& operator=(Subscription &&rhs) noexcept {
        if (&rhs == this)
            return *this;

        std::swap(m_id, rhs.m_id);
        std::swap(m_subject, rhs.m_subject);
        std::swap(m_observer, rhs.m_observer);

        return *this;
    }

    void unsubscribe() {
        m_subject->unsubscribe(*this);
    }

    void mute() {
        m_observer->mute();
    }

    void unmute() {
        m_observer->unmute();
    }

    bool isMuted() const {
        return m_observer->isMuted();
    }

    SubscriptionId getId() const {
        return m_id;
    }

    Subject_t* getSubject() const {
        return m_subject;
    }

    Observer_t* getObserver() const {
        return m_observer;
    }

    bool isValid() const {
        return m_subject != nullptr && m_subject->isSubscriptionValid(*this);
    }

private:
    Subscription(SubscriptionId id, Subject_t *subject, Observer_t *observer)
        : m_id(id), m_subject(subject), m_observer(observer) {}

private:
    SubscriptionId m_id {InvalidSubscriptionId};
    Subject_t *m_subject {nullptr};
    Observer_t *m_observer {nullptr};
};
}

#endif //TULZ_SUBSCRIPTION_H
