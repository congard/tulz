#ifndef TULZ_ETERNALOBSERVERAUTOPTR_H
#define TULZ_ETERNALOBSERVERAUTOPTR_H

#include <tulz/observer/ObserverAutoPtr.h>
#include <tulz/observer/EternalObserver.h>
#include <tulz/observer/EternalObserverFactory.h>

namespace tulz {
template<typename ...Args>
using EternalObserverAutoPtr = ObserverAutoPtr<EternalObserver, Args...>;
}

#endif //TULZ_ETERNALOBSERVERAUTOPTR_H
