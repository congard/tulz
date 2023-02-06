#ifndef TULZ_SUBJECT_H
#define TULZ_SUBJECT_H

#include <forward_list>

#include "Observer.h"

namespace tulz {
class Subject {
public:
    Subject();

    void subscribe(Observer *observer);
    void unsubscribe(Observer *observer);

    void subscribe(Observer &observer);
    void unsubscribe(Observer &observer);

    void notifyAll();

private:
    std::forward_list<Observer*> m_observers;
    decltype(m_observers)::iterator m_lastObserverIt;
};
}

#endif //TULZ_SUBJECT_H
