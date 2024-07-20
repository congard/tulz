#ifndef TULZ_ROUTINGKEY_H
#define TULZ_ROUTINGKEY_H

#include <tulz/observer/routing/RoutingLevelView.h>
#include <tulz/observer/routing/RoutingKeyLevel.h>

#include <vector>

namespace tulz {
/**
 * Represents routing key.
 */
class TULZ_API RoutingKey {
    friend class RoutingKeyBuilder;

public:
    RoutingLevelView view() const;

    int getLevelCount() const;

    const RoutingKeyLevel& getLevel(int index) const;

    operator RoutingLevelView() const;

private:
    RoutingKey();

private:
    std::vector<RoutingKeyLevel> m_levels;
};
} // tulz

#endif //TULZ_ROUTINGKEY_H
