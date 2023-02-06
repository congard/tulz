#ifndef TULZ_OBSERVERFUNCTION_H
#define TULZ_OBSERVERFUNCTION_H

#include <functional>

#include "Observer.h"

namespace tulz {
class ObserverFunction: public Observer {
public:
    using Function = std::function<void()>;

public:
    ObserverFunction() = default;
    explicit ObserverFunction(Function function);

    void notify() override;

private:
    Function m_function;
};
}

#endif //TULZ_OBSERVERFUNCTION_H
