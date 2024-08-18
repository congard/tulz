#ifndef TULZ_ETERNALOBSERVER_H
#define TULZ_ETERNALOBSERVER_H

#include <tulz/observer/Observer.h>

namespace tulz {
template<typename ...Args>
struct EternalObserverFactory;

template<typename ...Args>
class EternalObserver : public Observer<Args...> {
public:
    using Base = Observer<Args...>;
    using Factory = EternalObserverFactory<Args...>;

public:
    EternalObserver(Base::Func func, Base::Params params = {})
        : Base(std::move(func), std::move(params)) {}

    bool isValid() const override {
        return m_isValid;
    }

    void invalidate() override {
        m_isValid = false;
    }

private:
    bool m_isValid {true};
};
}

#endif //TULZ_ETERNALOBSERVER_H
