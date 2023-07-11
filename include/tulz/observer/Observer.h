#ifndef TULZ_OBSERVER_H
#define TULZ_OBSERVER_H

#include <functional>

namespace tulz {
template<typename ...Args>
using Observer = std::function<void(Args...)>;
}

#endif //TULZ_OBSERVER_H
