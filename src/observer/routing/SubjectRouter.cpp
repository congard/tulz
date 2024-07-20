#include <tulz/observer/routing/SubjectRouter.h>

#include <experimental/map>
#include <numeric>
#include <cassert>

namespace tulz {
SubjectRouter::SubjectRouter()
    : m_rootNode("") {}

void SubjectRouter::shrink(const RoutingKey &key) {
    m_rootNode.shrink(key);
}

bool SubjectRouter::exists(const RoutingKey &key) const {
    return m_rootNode.exists(key);
}

size_t SubjectRouter::depth() const {
    return m_rootNode.depth();
}

SubjectRouter::Node::Node(std::string name)
    : m_name(std::move(name)) {}

void SubjectRouter::Node::shrink(RoutingLevelView levelView) {
    if (!levelView.matches(m_name))
        return;

    // shrink the next level first
    if (!levelView.isLeaf()) {
        auto nextLevel = levelView.up();

        if (nextLevel.isRegex()) {
            for (auto & [name, node] : m_children) {
                node.shrink(nextLevel);
            }
        } else {
            if (auto it = m_children.find(nextLevel.asString()); it != m_children.end()) {
                it->second.shrink(nextLevel);
            }
        }
    }

    // erase empty children
    // C++20: std::erase_if
    std::experimental::erase_if(m_children, [](auto &p) {
        return p.second.isEmpty();
    });
}

bool SubjectRouter::Node::isEmpty() const {
    return (m_subject == nullptr || !m_subject->hasSubscriptions()) && m_children.empty();
}

bool SubjectRouter::Node::exists(RoutingLevelView levelView) const {
    if (!levelView.matches(m_name))
        return false;

    if (levelView.isLeaf())
        return true;

    auto nextLevel = levelView.up();

    if (nextLevel.isRegex()) {
        return std::any_of(m_children.begin(), m_children.end(), [nextLevel](const auto &p) {
            return p.second.exists(nextLevel);
        });
    } else {
        if (auto it = m_children.find(nextLevel.asString()); it != m_children.end())
            return it->second.exists(nextLevel);
        return false;
    }
}

size_t SubjectRouter::Node::depth() const {
    size_t maxDepth = 0;

    for (auto & [name, node] : m_children)
        maxDepth = std::max(maxDepth, node.depth());

    return 1 + maxDepth;
}

SubjectRouter::Node& SubjectRouter::Node::lookupNode(RoutingLevelView levelView) {
    assert(levelView.matches(m_name));

    if (levelView.isLeaf())
        return *this;

    auto nextLevel = levelView.up();

    // TODO: throw a human-readable error
    assert(!nextLevel.isRegex());

    auto &nextLevelName = nextLevel.asString();

    auto [it, isInserted] = m_children.insert({nextLevelName, Node(nextLevelName)});
    auto &node = it->second;

    return node.lookupNode(nextLevel);
}
} // tulz