#ifndef TULZ_SUBSCRIPTION_H
#define TULZ_SUBSCRIPTION_H

#include "Observer.h"

namespace tulz {
template<typename ...Args>
class Subject;

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

        std::swap(m_subject, rhs.m_subject);
        std::swap(m_observer, rhs.m_observer);

        return *this;
    }

    void unsubscribe() {
        m_subject->unsubscribe(*this);
    }

    Subject_t* getSubject() const {
        return m_subject;
    }

    bool isValid() const {
        return m_subject != nullptr && m_observer != nullptr;
    }

private:
    Subscription(Subject_t *subject, Observer_t *observer)
        : m_subject(subject), m_observer(observer) {}

private:
    Subject_t *m_subject {nullptr};
    Observer_t *m_observer {nullptr};
};
}

#endif //TULZ_SUBSCRIPTION_H
