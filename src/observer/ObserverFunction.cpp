#include <tulz/observer/ObserverFunction.h>

#include <utility>

namespace tulz {
ObserverFunction::ObserverFunction(Function function)
    : m_function(std::move(function)) {}

void ObserverFunction::notify() {
    if (m_function) {
        m_function();
    }
}
}
