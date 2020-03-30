#ifndef TULZ_MACROS_H
#define TULZ_MACROS_H

#define deletePtr(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; }
#define deletePtrArray(ptr) if (ptr != nullptr) { delete[] ptr; ptr = nullptr; }
#define getArraySize(array) (sizeof(array) / sizeof(array[0]))

#define switch_t(_val) \
{ \
    const auto &__val = _val; \
    if (false);

#define case_t(_val) \
    else if (__val == _val)

#define default_t \
    else

#define switch_t_end \
}

#define namespace_t(_name) namespace _name {
#define namespace_t_end }

#endif //TULZ_MACROS_H
