#ifndef SPACE_EXPLORER_RUNNABLE_H
#define SPACE_EXPLORER_RUNNABLE_H

#include <type_traits>

namespace tulz {
class Runnable {
public:
    virtual ~Runnable();

    virtual void run() = 0;

public:
    template<typename T>
    using isRunnable = typename std::is_base_of<Runnable, std::remove_pointer_t<T>>;
};
}

#endif //SPACE_EXPLORER_RUNNABLE_H
