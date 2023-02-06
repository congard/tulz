#include <tulz/observer/Observer.h>
#include <tulz/observer/Subject.h>

namespace tulz {
Observer::Observer()
    : m_subject(nullptr) {}

Observer::~Observer() {
    if (m_subject) {
        m_subject->unsubscribe(this);
    }
}

Subject* Observer::getSubject() const {
    return m_subject;
}
}
