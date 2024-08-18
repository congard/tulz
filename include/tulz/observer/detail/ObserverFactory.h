#ifndef TULZ_OBSERVERFACTORY_H
#define TULZ_OBSERVERFACTORY_H

#include <tulz/observer/Observer.h>

#include <concepts>
#include <utility>

namespace tulz::detail {
template<typename F, typename ...Args>
concept IsObserverFactoryFunctor = requires(F f, Observer<Args...>::Func callable) {
    ObserverPtr<Args...>{f.template operator()<Args...>(std::move(callable))};
};

/**
 * @tparam F The functor that produces observer of desired type.
 * @tparam Args The arguments that will be accepted by the produced observer.
 * @see `IsObserverFactoryFunctor`
 */
template<typename F, typename ...Args>
struct ObserverFactory {
    using ObserverFunction = typename Observer<Args...>::Func;
    using ObserverSelfView = typename Observer<Args...>::SelfView;

    /**
     * "Simple" or "Passthrough" operator().
     */
    template<typename C>
    auto operator()(C &&callable)
        requires IsObserverFactoryFunctor<F, Args...> &&
                 std::convertible_to<C, ObserverFunction>
    {
        F factory{};
        return factory.template operator()<Args...>(std::forward<C>(callable));
    }

    /**
     * Produces an observer with an additional `self` argument.
     * @tparam C The callable that accepts `SelfView` as its first argument.
     */
    template<typename C>
    auto operator()(C &&callable)
        requires IsObserverFactoryFunctor<F, Args...> &&
                 std::invocable<C, ObserverSelfView, Args...>
    {
        F factory{};

        ObserverPtr<Args...> observer {factory.template operator()<Args...>()};
        *observer = [self = observer.get(), callable = std::forward<C>(callable)](Args... args) {
            callable(self, std::forward<Args>(args)...);
        };

        return observer;
    }
};
}

#endif //TULZ_OBSERVERFACTORY_H
