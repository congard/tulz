#ifndef TULZ_OBSERVERFACTORY_H
#define TULZ_OBSERVERFACTORY_H

#include <tulz/observer/Observer.h>

#include <concepts>
#include <utility>

namespace tulz::detail {
template<typename F, typename ...Args>
concept IsObserverFactoryFunctor = requires(F f, Args... args) {
    ObserverPtr<Args...>{f(std::forward<Args>(args)...)};
};

/**
 * @tparam F The functor that produces observer of desired type
 */
template<typename F, typename ...Args>
struct ObserverFactory {
    template<typename C>
    auto operator()(C &&callable)
        requires IsObserverFactoryFunctor<F, Args...> &&
                 std::invocable<C, Args...>
    {
        F factory{};
        return factory.template operator()<Args...>(std::forward<C>(callable));
    }

    template<typename C>
    auto operator()(C &&callable)
        requires IsObserverFactoryFunctor<F, Args...> &&
                 std::invocable<C, typename Observer<Args...>::SelfView, Args...>
    {
        F factory{};

        ObserverPtr<Args...> observer = factory.template operator()<Args...>();
        *observer = [self = observer.get(), callable = std::forward<C>(callable)](Args... args) {
            callable(self, std::forward<Args>(args)...);
        };

        return observer;
    }
};
}

#endif //TULZ_OBSERVERFACTORY_H
