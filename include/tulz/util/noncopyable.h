#ifndef TULZ_NONCOPYABLE_H
#define TULZ_NONCOPYABLE_H

namespace tulz {
class noncopyable {
public:
    noncopyable() = default;
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};
}

#endif //TULZ_NONCOPYABLE_H
