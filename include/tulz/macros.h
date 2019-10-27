#ifndef TULZ_MACROS_H
#define TULZ_MACROS_H

#define deletePtr(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; }
#define deletePtrArray(ptr) if (ptr != nullptr) { delete[] ptr; ptr = nullptr; }
#define getArraySize(array) (sizeof(array) / sizeof(array[0]))

#endif //TULZ_MACROS_H
