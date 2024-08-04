#ifndef TULZ_ETERNALOBSERVERFACTORY_H
#define TULZ_ETERNALOBSERVERFACTORY_H

#include <tulz/observer/EternalObserver.h>
#include <tulz/observer/detail/ObserverFactory.h>

namespace tulz {
namespace detail {
using EternalObserverFactory_t = decltype([]<typename ...Args>(EternalObserver<Args...>::Func f = {}) {
    return std::make_unique<EternalObserver<Args...>>(std::move(f));
});
}

template<typename ...Args>
struct EternalObserverFactory : detail::ObserverFactory<detail::EternalObserverFactory_t, Args...> {};
}

#endif //TULZ_ETERNALOBSERVERFACTORY_H
