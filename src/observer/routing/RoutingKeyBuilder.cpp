#include <tulz/observer/routing/RoutingKeyBuilder.h>

namespace tulz {
RoutingKeyBuilder::RoutingKeyBuilder() {
    m_key.m_levels.emplace_back(""); // root node
}

RoutingKeyBuilder& RoutingKeyBuilder::level(std::string name) {
    m_key.m_levels.emplace_back(std::move(name));
    return *this;
}

RoutingKeyBuilder& RoutingKeyBuilder::level(std::regex regex) {
    m_key.m_levels.emplace_back(std::move(regex));
    return *this;
}

RoutingKeyBuilder& RoutingKeyBuilder::all() {
    m_key.m_levels.emplace_back(std::regex {".*"});
    return *this;
}

RoutingKey RoutingKeyBuilder::build() {
    return std::move(m_key);
}
} // tulz