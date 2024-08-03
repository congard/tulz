#ifndef TULZ_USUBSCRIPTION_H
#define TULZ_USUBSCRIPTION_H

#include "Subscription.h"

#include <memory>

namespace tulz {
/**
 * Universal Subscription.
 * The class that represents a type-erased subscription.
 */
class USubscription {
protected:
    class Invoker;

    template<typename ...Args>
    class DefaultInvoker;

public:
    template<typename ...Args>
    USubscription(Subscription<Args...> subscription);

    USubscription(USubscription &&other) noexcept;
    USubscription& operator=(USubscription &&rhs) noexcept;

    virtual ~USubscription() = default;

    Invoker* operator->();
    const Invoker* operator->() const;

protected:
    explicit USubscription(std::unique_ptr<Invoker> invoker);

private:
    std::unique_ptr<Invoker> m_invoker;
};

class USubscription::Invoker {
public:
    virtual ~Invoker() = default;

    virtual void unsubscribe() = 0;

    virtual void mute() = 0;
    virtual void unmute() = 0;
    virtual bool isMuted() const = 0;

    virtual bool isValid() const = 0;
};

template<typename ...Args>
class USubscription::DefaultInvoker: public Invoker {
protected:
    using Subscription_t = Subscription<Args...>;

public:
    explicit DefaultInvoker(Subscription_t &subscription)
        : m_subscription(std::move(subscription)) {}

    void unsubscribe() override {
        m_subscription.unsubscribe();
    }

    void mute() override {
        m_subscription.mute();
    }

    void unmute() override {
        m_subscription.unmute();
    }

    bool isMuted() const override {
        return m_subscription.isMuted();
    }

    bool isValid() const override {
        return m_subscription.isValid();
    }

private:
    Subscription_t m_subscription;
};

template<typename ...Args>
USubscription::USubscription(Subscription<Args...> subscription)
    : m_invoker(std::make_unique<DefaultInvoker<Args...>>(subscription)) {}

inline USubscription::USubscription(std::unique_ptr<Invoker> invoker)
    : m_invoker(std::move(invoker)) {}

inline USubscription::USubscription(USubscription &&other) noexcept
    : m_invoker(std::move(other.m_invoker)) {}

inline USubscription& USubscription::operator=(USubscription &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    m_invoker = std::move(rhs.m_invoker);
    return *this;
}

inline USubscription::Invoker* USubscription::operator->() {
    return m_invoker.get();
}

inline const USubscription::Invoker* USubscription::operator->() const {
    return m_invoker.get();
}
}

#endif //TULZ_USUBSCRIPTION_H
