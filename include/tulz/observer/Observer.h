#ifndef TULZ_OBSERVER_H
#define TULZ_OBSERVER_H

namespace tulz {
class Subject;

class Observer {
    friend class Subject;

public:
    Observer();
    virtual ~Observer();

    virtual void notify() = 0;

    Subject* getSubject() const;

protected:
    Subject *m_subject;
};
}

#endif //TULZ_OBSERVER_H
