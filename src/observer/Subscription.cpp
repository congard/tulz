#include <tulz/observer/Subscription.h>
#include <tulz/observer/Subject.h>

namespace tulz {
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
