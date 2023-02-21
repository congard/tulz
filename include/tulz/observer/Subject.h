#ifndef TULZ_SUBJECT_H
#define TULZ_SUBJECT_H

#include <forward_list>
#include <set>

#include "Observer.h"
#include "Subscription.h"

namespace tulz {
class Subject {
public:
    Subject();

    Subscription subscribe(const Observer &observer);
    void unsubscribe(Subscription &subscription);

    void notify();

private:
    std::forward_list<Observer> m_observers;
    std::set<Observer*> m_observersSet;
};
}

#endif //TULZ_SUBJECT_H
