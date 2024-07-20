#ifndef TULZ_RUNNABLE_H
#define TULZ_RUNNABLE_H

#include <tulz/export.h>

#include <type_traits>

namespace tulz {
class TULZ_API Runnable {
public:
    virtual ~Runnable();

    virtual void run() = 0;

public:
    template<typename T>
    using isRunnable = typename std::is_base_of<Runnable, std::remove_pointer_t<T>>;
};
}

#endif //TULZ_RUNNABLE_H
