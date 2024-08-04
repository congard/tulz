#ifndef TULZ_OBSERVERAUTOPTR_H
#define TULZ_OBSERVERAUTOPTR_H

#include <tulz/observer/Observer.h>
#include <tulz/observer/EternalObserver.h>

#include <concepts>

namespace tulz {
/**
 * @brief A smart pointer wrapper for observer objects.
 *
 * The `ObserverAutoPtr` class accepts three different types of objects:
 *
 * 1. Invocable objects: When an invocable object (e.g., lambda, function, functor) is provided,
 *    a new default observer will be created.
 * 2. Unique pointers of derived observers: If a unique pointer to a derived observer type is passed,
 *    the ownership will be transferred to the `ObserverAutoPtr`.
 * 3. Raw pointers of derived observers: When a raw pointer to a derived observer object is given,
 *    the ownership will be transferred to the `ObserverAutoPtr`.
 *
 * @tparam Args The template parameter pack representing the types of arguments for the observer.
 */
template<typename ...Args>
class ObserverAutoPtr {
public:
    using BaseObserver = Observer<Args...>;
    using DefaultObserver = EternalObserver<Args...>;
    using Ptr = std::unique_ptr<BaseObserver>;

public:
    template<typename T>
    ObserverAutoPtr(T &&val) requires std::invocable<T, Args...>
        : m_ptr(std::make_unique<DefaultObserver>(std::forward<T>(val))) {}

    template<typename T>
    ObserverAutoPtr(std::unique_ptr<T> ptr) requires std::derived_from<T, BaseObserver>
        : m_ptr(std::move(ptr)) {}

    ObserverAutoPtr(BaseObserver *ptr)
        : m_ptr(ptr) {}

    Ptr operator*() {
        return std::move(m_ptr);
    }

    Ptr pointer() {
        return std::move(m_ptr);
    }

private:
    Ptr m_ptr;
};
}

#endif //TULZ_OBSERVERAUTOPTR_H
