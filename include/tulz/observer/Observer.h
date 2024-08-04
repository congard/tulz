#ifndef TULZ_OBSERVER_H
#define TULZ_OBSERVER_H

#include <functional>
#include <algorithm>
#include <memory>

namespace tulz {
template<typename ...Args>
class Observer {
public:
    using Func = std::function<void(Args...)>;

    struct Params {
        bool mute {false};
    };

    class SelfView {
    public:
        SelfView(Observer *self)
            : m_self(self) {}

        auto operator->() const {
            return m_self;
        }

    private:
        Observer *m_self;
    };

public:
    Observer() = default;
    virtual ~Observer() = default;

    Observer(Func func, Params params = {})
        : m_func(std::move(func)),
          m_params(std::move(params)) {}

    Observer(const Observer &that)
        : Observer(that.m_func, that.m_params) {}

    Observer(Observer &&that) noexcept {
        *this = std::move(that);
    }

    Observer& operator=(Func func) {
        m_func = std::move(func);
        return *this;
    }

    Observer& operator=(const Observer &that) {
        if (this == &that)
            return *this;
        m_func = that.m_func;
        m_params = that.m_params;
        return *this;
    }

    Observer& operator=(Observer &&that) noexcept {
        if (this == &that)
            return *this;
        std::swap(m_func, that.m_func);
        std::swap(m_params, that.m_params);
        return *this;
    }

    virtual void operator()(Args... args) {
        if (!isMuted() && isValid()) {
            m_func(std::forward<Args>(args)...);
        }
    }

    virtual bool isValid() const = 0;

    virtual void invalidate() = 0;

    void mute() {
        m_params.mute = true;
    }

    void unmute() {
        m_params.mute = false;
    }

    bool isMuted() const {
        return m_params.mute;
    }

private:
    Func m_func;
    Params m_params;
};

template<typename ...Args>
using ObserverPtr = std::unique_ptr<Observer<Args...>>;
}

#endif //TULZ_OBSERVER_H
