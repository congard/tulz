#include <tulz/observer/routing/RoutingKey.h>

#include <cassert>

namespace tulz {
RoutingLevelView RoutingKey::view() const {
    return RoutingLevelView(*this);
}

int RoutingKey::getLevelCount() const {
    return static_cast<int>(m_levels.size());
}

const RoutingKeyLevel& RoutingKey::getLevel(int index) const {
    assert(0 <= index && index < getLevelCount());
    return m_levels[index];
}

RoutingKey::operator RoutingLevelView() const {
    return view();
}

RoutingKey::RoutingKey() = default;
} // tulz