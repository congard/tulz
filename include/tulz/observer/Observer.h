#ifndef TULZ_OBSERVER_H
#define TULZ_OBSERVER_H

#include <functional>

namespace tulz {
using Observer = std::function<void()>;
}

#endif //TULZ_OBSERVER_H
