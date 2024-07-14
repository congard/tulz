#ifndef TULZ_ROUTINGKEYVIEW_H
#define TULZ_ROUTINGKEYVIEW_H

#include <tulz/observer/routing/RoutingKeyLevel.h>

#include <string_view>

namespace tulz {
class RoutingKey;

class RoutingLevelView {
public:
    explicit RoutingLevelView(const RoutingKey &key, int level = 0);

    RoutingLevelView up() const;
    RoutingLevelView down() const;

    bool matches(std::string_view levelName) const;
    bool isRoot() const;
    bool isLeaf() const;
    bool isRegex() const;

    int getLevelIndex() const;
    int getLevelCount() const;

    const RoutingKeyLevel& getLevel() const;

    const std::string& asString() const;
    const std::regex& asRegex() const;

private:
    const RoutingKey &m_key;
    int m_level;
};
} // tulz

#endif //TULZ_ROUTINGKEYVIEW_H
