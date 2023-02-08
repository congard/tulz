#include <tulz/observer/Subscription.h>
#include <tulz/observer/Subject.h>

namespace tulz {
Subscription::Subscription(Subscription &&rhs) noexcept {
    *this = std::move(rhs);
}

Subscription& Subscription::operator=(Subscription &&rhs) noexcept {
    if (&rhs == this)
        return *this;

    std::swap(m_subject, rhs.m_subject);
    std::swap(m_observer, rhs.m_observer);

    return *this;
}

void Subscription::unsubscribe() {
    m_subject->unsubscribe(*this);
}

Subject* Subscription::getSubject() const {
    return m_subject;
}

bool Subscription::isValid() const {
    return m_subject != nullptr && m_observer != nullptr;
}

Subscription::Subscription(Subject *subject, Observer *observer)
    : m_subject(subject), m_observer(observer) {}
}
