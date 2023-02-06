#include <tulz/observer/Subject.h>
#include <algorithm>

namespace tulz {
Subject::Subject()
    : m_lastObserverIt(m_observers.before_begin()) {}

void Subject::subscribe(Observer *observer) {
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);

    // check if this observer is already added
    if (it != m_observers.end())
        return;

    observer->m_subject = this;

    m_observers.insert_after(m_lastObserverIt, observer);
    ++m_lastObserverIt;
}

void Subject::unsubscribe(Observer *observer) {
    m_observers.remove(observer);
    m_lastObserverIt = m_observers.before_begin();
    for (auto it = m_observers.begin(); it != m_observers.end(); m_lastObserverIt = it++);
}

void Subject::notifyAll() {
    for (auto observer : m_observers) {
        observer->notify();
    }
}
}
