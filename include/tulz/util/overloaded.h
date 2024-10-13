#ifndef TULZ_OVERLOADED_H
#define TULZ_OVERLOADED_H

namespace tulz {
template<typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
}

#endif //TULZ_OVERLOADED_H
