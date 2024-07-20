#ifndef TULZ_ROUTINGKEYBUILDER_H
#define TULZ_ROUTINGKEYBUILDER_H

#include <tulz/observer/routing/RoutingKey.h>
#include <tulz/util/noncopyable.h>

namespace tulz {
class RoutingKeyBuilder : noncopyable {
public:
    RoutingKeyBuilder();

    template<typename... Args>
    explicit RoutingKeyBuilder(Args&&... args) {
        m_key.m_levels.emplace_back(""); // root node
        (level(std::forward<Args>(args)), ...);
    }

    RoutingKeyBuilder& level(std::string name);
    RoutingKeyBuilder& level(std::regex regex);
    RoutingKeyBuilder& all();

    RoutingKey build();

private:
    RoutingKey m_key;
};
} // tulz

#endif //TULZ_ROUTINGKEYBUILDER_H
