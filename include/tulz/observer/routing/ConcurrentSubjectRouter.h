#ifndef TULZ_CONCURRENTSUBJECTROUTER_H
#define TULZ_CONCURRENTSUBJECTROUTER_H

#include <tulz/observer/routing/SubjectRouter.h>
#include <tulz/observer/USubscription.h>
#include <tulz/threading/rwp/Resource.h>
#include <tulz/threading/rwp/ReadLock.h>
#include <tulz/threading/rwp/WriteLock.h>

namespace tulz {
class ConcurrentSubjectRouter {
    class Subscription : public USubscription {
        template<typename ...Args>
        class ConcurrentInvoker;

    public:
        template<typename ...Args>
        Subscription(rwp::Resource &resource, tulz::Subscription<Args...> subscription);

        using USubscription::operator->;
    };

public:
    inline ConcurrentSubjectRouter() = default;

    template<typename ...Args>
    size_t notify(const RoutingKey &key, Args&&... args) {
        rwp::ReadLock lock {m_resource};
        return m_router.notify(key, std::forward<Args>(args)...);
    }

    template<typename ...Args, typename O>
    USubscription subscribe(const RoutingKey &key, O &&observer) {
        rwp::WriteLock lock {m_resource};
        return Subscription(m_resource, m_router.subscribe<Args...>(key, std::forward<O>(observer)));
    }

    inline void shrink(const RoutingKey &key) {
        rwp::WriteLock lock {m_resource};
        m_router.shrink(key);
    }

    inline bool exists(const RoutingKey &key) const {
        rwp::ReadLock lock {m_resource};
        return m_router.exists(key);
    }

    inline size_t depth() const {
        rwp::ReadLock lock {m_resource};
        return m_router.depth();
    }

private:
    SubjectRouter m_router;
    mutable rwp::Resource m_resource;
};

template<typename ...Args>
class ConcurrentSubjectRouter::Subscription::ConcurrentInvoker :
        public USubscription::DefaultInvoker<Args...>
{
public:
    explicit ConcurrentInvoker(rwp::Resource &resource, DefaultInvoker<Args...>::Subscription_t &subscription)
        : DefaultInvoker<Args...>(subscription),
          m_resource(resource) {}

    void unsubscribe() override {
        rwp::WriteLock lock {m_resource};
        DefaultInvoker<Args...>::unsubscribe();
    }

private:
    rwp::Resource &m_resource;
};

template<typename ...Args>
ConcurrentSubjectRouter::Subscription::Subscription(rwp::Resource &resource, tulz::Subscription<Args...> subscription)
    : USubscription(std::make_unique<ConcurrentInvoker<Args...>>(resource, subscription)) {}
} // tulz

#endif //TULZ_CONCURRENTSUBJECTROUTER_H
