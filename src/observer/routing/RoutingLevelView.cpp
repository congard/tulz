#include <tulz/observer/routing/RoutingLevelView.h>
#include <tulz/observer/routing/RoutingKey.h>

#include <cassert>

namespace tulz {
RoutingLevelView::RoutingLevelView(const RoutingKey &key, int level)
    : m_key(key), m_level(level) {}

RoutingLevelView RoutingLevelView::up() const {
    assert(!isLeaf());
    return RoutingLevelView(m_key, m_level + 1);
}

RoutingLevelView RoutingLevelView::down() const {
    assert(!isRoot());
    return RoutingLevelView(m_key, m_level - 1);
}

bool RoutingLevelView::matches(std::string_view levelName) const {
    auto &level = getLevel();

    if (auto str = std::get_if<std::string>(&level); str != nullptr) {
        return levelName == *str;
    } else if (auto regex = std::get_if<std::regex>(&level); regex != nullptr) {
        return std::regex_match(levelName.begin(), levelName.end(), *regex);
    }

    assert(false);
}

bool RoutingLevelView::isRoot() const {
    return m_level == 0;
}

bool RoutingLevelView::isLeaf() const {
    return getLevelIndex() == getLevelCount() - 1;
}

bool RoutingLevelView::isRegex() const {
    return std::get_if<std::regex>(&getLevel()) != nullptr;
}

int RoutingLevelView::getLevelIndex() const {
    return m_level;
}

int RoutingLevelView::getLevelCount() const {
    return m_key.getLevelCount();
}

const RoutingKeyLevel& RoutingLevelView::getLevel() const {
    return m_key.getLevel(m_level);
}

const std::string& RoutingLevelView::asString() const {
    return std::get<std::string>(getLevel());
}

const std::regex& RoutingLevelView::asRegex() const {
    return std::get<std::regex>(getLevel());
}
} // tulz