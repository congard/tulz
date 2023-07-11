#ifndef TULZ_OBSERVABLE_H
#define TULZ_OBSERVABLE_H

#include "Subject.h"

namespace tulz {
template<typename T>
class Observable: public Subject<T&> {
public:
    using type = T;

public:
    Observable() = default;

    explicit Observable(T &&val)
        : m_val(val) {}

    Observable(const Observable&) = delete;

    Observable(Observable &&rhs) noexcept {
        std::swap(m_val, rhs.m_val);
    }

    Observable& operator=(T &&val) {
        m_val = val;
        this->notify(get());
        return *this;
    }

    Observable& operator=(const Observable&) = delete;

    Observable& operator=(Observable &&rhs) noexcept {
        std::swap(m_val, rhs.m_val);
        return *this;
    }

    T& operator*() {
        return m_val;
    }

    const T& operator*() const {
        return m_val;
    }

    T& get() {
        return m_val;
    }

    const T& get() const {
        return m_val;
    }

protected:
    T m_val;
};
}

#endif //TULZ_OBSERVABLE_H
