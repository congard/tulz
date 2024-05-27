#ifndef TULZ_NONMOVABLE_H
#define TULZ_NONMOVABLE_H

namespace tulz {
class nonmovable {
public:
    nonmovable() = default;
    nonmovable(nonmovable&&) = delete;
    nonmovable& operator=(nonmovable&&) = delete;
};
}

#endif //TULZ_NONMOVABLE_H
