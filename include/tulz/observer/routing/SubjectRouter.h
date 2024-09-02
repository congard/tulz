#ifndef TULZ_SUBJECTROUTER_H
#define TULZ_SUBJECTROUTER_H

#include <tulz/observer/Subject.h>
#include <tulz/observer/EternalObserverAutoPtr.h>
#include <tulz/observer/routing/RoutingKey.h>

#include <memory>
#include <map>

namespace tulz {
template<typename S, typename F>
concept IsSubjectFactory = std::is_invocable_r_v<S*, F>;

class TULZ_API SubjectRouter {
    template<typename ...Args>
    using Subject_t = Subject<Args...>;

    using DefaultSubject_t = Subject_t<>;

    template<typename ...Args>
    using ObserverAutoPtr_t = EternalObserverAutoPtr<Args...>;

public:
    SubjectRouter();

    /**
     * Notifies observers using the routing key.
     * @tparam Args The types of arguments to pass.
     * @note The destination observers must accept the
     * arguments of the specified types. Otherwise the
     * behaviour is undefined.
     * @param key The routing key. Can contain regex.
     * @param args The arguments to pass.
     * @return The number of observers notified.
     */
    template<typename ...Args>
    size_t notify(const RoutingKey &key, Args&&... args) {
        return m_rootNode.notify(key, std::forward<Args>(args)...);
    }

    /**
     * Subscribes using the routing key. If the corresponding
     * subject does not exist, creates a new one.
     * @tparam Args The types of observer arguments.
     * @note The destination subject must accept the
     * arguments of the specified types. Otherwise the
     * behaviour is undefined.
     * @tparam C The type of callable.
     * @param key The routing key. Cannot contain regex.
     * @param callable The callable (callback) to subscribe.
     * @return The subscription.
     */
    template<typename ...Args, typename O>
    Subscription<Args...> subscribe(const RoutingKey &key, O &&observer) {
        return m_rootNode.subscribe(key, *ObserverAutoPtr_t<Args...>(std::forward<O>(observer)));
    }

    /**
     * Optimizes space usage by removing unused nodes.
     * @note Shrinking will take place "up to key",
     * not "starting from key".
     * @param key The routing key. Can contain regex.
     */
    void shrink(const RoutingKey &key);

    /**
     * Checks whether the nodes exist or not.
     * @param key The routing key. Can contain regex.
     * @return `true` if at least one node matches the key, `false` otherwise.
     */
    bool exists(const RoutingKey &key) const;

    /**
     * Calculates the depth of the tree.
     * @note Takes into account the root node, i.e.
     * the minimal value that can be returned by this
     * function is 1.
     * @return The tree depth.
     */
    size_t depth() const;

private:
    class TULZ_API Node {
    public:
        explicit Node(std::string name);

        template<typename ...Args>
        size_t notify(RoutingLevelView levelView, Args &&...args);

        template<typename ...Args, typename F>
        Subscription<Args...> subscribe(
                RoutingLevelView levelView,
                ObserverPtr<Args...> observer,
                F &&subjectFactory) requires IsSubjectFactory<Subject_t<Args...>, F>;

        template<typename ...Args>
        Subscription<Args...> subscribe(RoutingLevelView levelView, ObserverPtr<Args...> observer) {
            return subscribe(levelView, std::move(observer), [] { return new Subject_t<Args...>(); });
        }

        void shrink(RoutingLevelView levelView);

        /**
         * The Node is considered empty if its subject has no subscriptions
         * and it doesn't have any children.
         * @return `true` if the above conditions are met, `false` otherwise.
         */
        bool isEmpty() const;

        bool exists(RoutingLevelView levelView) const;

        size_t depth() const;

    private:
        std::string m_name;
        std::unique_ptr<DefaultSubject_t> m_subject;
        std::map<std::string, Node> m_children;

        using ChildRecord = decltype(m_children)::value_type;

    private:
        /**
         * Finds a node using the specific key. I.e.:
         * <ul>
         *   <li>/foo/bar: specific key (valid)</li>
         *   <li>/.+/bar: non-specific key (invalid)</li>
         * </ul>
         * @param levelView The view for routing levels.
         * @return Reference to the node; if the node(s) does not exist, it will be created.
         */
        Node& lookupNode(RoutingLevelView levelView);
    };

private:
    Node m_rootNode;
};

template<typename ...Args>
size_t SubjectRouter::Node::notify(RoutingLevelView levelView, Args &&...args) {
    if (!levelView.matches(m_name))
        return 0;

    if (levelView.isLeaf()) {
        if (m_subject != nullptr) {
            auto &subject = *reinterpret_cast<Subject_t<Args...>*>(m_subject.get());
            subject.notify(std::forward<Args>(args)...);
            return 1;
        }
    } else {
        auto nextLevel = levelView.up();

        if (nextLevel.isRegex()) {
            size_t notifyCount = 0;

            for (auto & [name, node] : m_children)
                notifyCount += node.notify(nextLevel, args...);

            return notifyCount;
        } else {
            if (auto it = m_children.find(nextLevel.asString()); it != m_children.end()) {
                return it->second.notify(nextLevel, std::forward<Args>(args)...);
            }
        }
    }

    return 0;
}

template<typename ...Args, typename F>
Subscription<Args...>
SubjectRouter::Node::subscribe(
    RoutingLevelView levelView,
    ObserverPtr<Args...> observer,
    F &&subjectFactory
) requires IsSubjectFactory<Subject_t<Args...>, F> {
    auto &node = lookupNode(levelView);

    if (node.m_subject == nullptr) {
        auto subject = static_cast<Subject_t<Args...>*>(subjectFactory());
        node.m_subject.reset(reinterpret_cast<DefaultSubject_t*>(subject));
    }

    auto &dstSubject = *reinterpret_cast<Subject_t<Args...>*>(node.m_subject.get());

    return dstSubject.subscribe(std::move(observer));
}
} // tulz

#endif //TULZ_SUBJECTROUTER_H
