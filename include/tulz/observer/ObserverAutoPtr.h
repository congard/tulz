#ifndef TULZ_OBSERVERAUTOPTR_H
#define TULZ_OBSERVERAUTOPTR_H

#include <tulz/observer/Observer.h>

#include <concepts>

namespace tulz {
/**
 * @brief A smart pointer wrapper for observer objects.
 *
 * The `ObserverAutoPtr` class accepts three different types of objects:
 *
 * 1. Invocable objects: When an invocable object (e.g., lambda, function, functor) is provided,
 *    a new default observer will be created using the factory of provided ObserverType.
 * 2. Unique pointers of derived observers: If a unique pointer to a derived observer type is passed,
 *    the ownership will be transferred to the `ObserverAutoPtr`.
 * 3. Raw pointers of derived observers: When a raw pointer to a derived observer object is given,
 *    the ownership will be transferred to the `ObserverAutoPtr`.
 *
 * @tparam ObserverType The observer which factory will be used in case 1.
 * @tparam Args The template parameter pack representing the types of arguments for the observer.
 */
template<template<typename...> class ObserverType, typename ...Args>
class ObserverAutoPtr {
public:
    using BaseObserver_t = Observer<Args...>;
    using Observer_t = ObserverType<Args...>;
    using Ptr_t = std::unique_ptr<BaseObserver_t>;

public:
    template<typename T>
    requires std::invocable<T, Args...> ||
             std::invocable<T, typename Observer_t::SelfView, Args...>
    ObserverAutoPtr(T &&val)
        : m_ptr(typename Observer_t::Factory{}(std::forward<T>(val))) {}

    template<typename T>
    requires std::derived_from<T, BaseObserver_t>
    ObserverAutoPtr(std::unique_ptr<T> ptr)
        : m_ptr(std::move(ptr)) {}

    ObserverAutoPtr(BaseObserver_t *ptr)
        : m_ptr(ptr) {}

    Ptr_t operator*() {
        return std::move(m_ptr);
    }

    Ptr_t pointer() {
        return std::move(m_ptr);
    }

private:
    Ptr_t m_ptr;
};
}

#endif //TULZ_OBSERVERAUTOPTR_H
