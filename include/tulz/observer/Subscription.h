#ifndef TULZ_SUBSCRIPTION_H
#define TULZ_SUBSCRIPTION_H

#include "Observer.h"

namespace tulz {
class Subject;

class Subscription {
    friend class Subject;

public:
    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;

    Subscription(Subscription&&) noexcept;
    Subscription& operator=(Subscription&&) noexcept;

    void unsubscribe();

    Subject* getSubject() const;

    bool isValid() const;

private:
    Subscription(Subject *subject, Observer *observer);

private:
    Subject *m_subject {nullptr};
    Observer *m_observer {nullptr};
};
}

#endif //TULZ_SUBSCRIPTION_H
