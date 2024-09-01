#ifndef TULZ_OBSERVABLE_H
#define TULZ_OBSERVABLE_H

#include "Subject.h"

namespace tulz {
template<
    typename T,
    typename Eq = std::equal_to<T>,
    template<typename...> class SubjectType = tulz::Subject>
requires
    std::is_invocable_r_v<bool, Eq, const T&, const T&> &&
    std::derived_from<SubjectType<T>, tulz::Subject<T>>
class Observable {
public:
    using type = T;
    using Subject_t = SubjectType<T&>;

public:
    Observable() = default;

    template<typename V = T>
    Observable(V &&val, Eq eq = {})
        : m_val(std::forward<V>(val)),
          m_eq(std::move(eq)) {}

    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;

    Observable(Observable&&) noexcept = default;
    Observable& operator=(Observable&&) noexcept = default;

    template<typename V = T>
    Observable& operator=(V &&val) {
        if (!m_eq(m_val, val)) {
            m_val = std::forward<V>(val);
            m_subject.notify(m_val);
        }
        return *this;
    }

    auto subscribe(Subject_t::ObserverAutoPtr_t observer) {
        return m_subject.subscribe(std::move(observer));
    }

    T& operator*() {
        return m_val;
    }

    const T& operator*() const {
        return m_val;
    }

    T& value() {
        return m_val;
    }

    const T& value() const {
        return m_val;
    }

    template<typename C>
    requires std::invocable<C, T&>
    void apply(C &&callable) {
        auto old = m_val;

        callable(m_val);

        if (!m_eq(old, m_val)) {
            m_subject.notify(m_val);
        }
    }

    template<typename V = T>
    Observable& operator+=(V &&other) {
        apply([other = std::forward<V>(other)](T &val) mutable {
            val += std::forward<V>(other);
        });
        return *this;
    }

    template<typename V = T>
    Observable& operator-=(V &&other) {
        apply([other = std::forward<V>(other)](T &val) mutable {
            val -= std::forward<V>(other);
        });
        return *this;
    }

    template<typename V = T>
    Observable& operator*=(V &&other) {
        apply([other = std::forward<V>(other)](T &val) mutable {
            val *= std::forward<V>(other);
        });
        return *this;
    }

    template<typename V = T>
    Observable& operator/=(V &&other) {
        apply([other = std::forward<V>(other)](T &val) mutable {
            val /= std::forward<V>(other);
        });
        return *this;
    }

    // postfix increment
    T operator++(int) {
        auto prev = m_val;
        ++m_val;
        m_subject.notify(m_val);
        return prev;
    }

    // prefix increment
    T& operator++() {
        ++m_val;
        m_subject.notify(m_val);
        return m_val;
    }

    // postfix decrement
    T operator--(int) {
        auto prev = m_val;
        --m_val;
        m_subject.notify(m_val);
        return prev;
    }

    // prefix decrement
    T& operator--() {
        --m_val;
        m_subject.notify(m_val);
        return m_val;
    }

protected:
    Subject_t m_subject;
    T m_val;
    Eq m_eq;
};

using ObservableChar = Observable<char>;
using ObservableUChar = Observable<unsigned char>;
using ObservableShort = Observable<short>;
using ObservableUShort = Observable<unsigned short>;
using ObservableInt = Observable<int>;
using ObservableUInt = Observable<unsigned int>;
using ObservableLong = Observable<long>;
using ObservableULong = Observable<unsigned long>;
using ObservableFloat = Observable<float>;
using ObservableDouble = Observable<double>;
}

#endif //TULZ_OBSERVABLE_H
