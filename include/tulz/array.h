#ifndef TULZ_ARRAY_H
#define TULZ_ARRAY_H

#include <cstddef>

namespace tulz {

/**
 * Container for C static array
 * @tparam T
 */
template <typename T>
class Array {
public:
    T *m_array = nullptr;
    size_t m_size = 0;

    explicit Array(T *const array, const size_t size) {
        m_array = array;
        m_size = size;
    }

    explicit Array(const size_t size) {
        m_size = size;
        m_array = new T[size];
    }

    Array() = default;

    // copy constructor
    Array(const Array<T> &src) {
        m_size = src.m_size;
        m_array = new T[m_size];
        for (size_t i = 0; i < m_size; i++)
            m_array[i] = src.m_array[i];
    }

    // move constructor
    Array(Array<T> &&src) noexcept {
        src.swap(*this);
    }

    // copy operator
    Array& operator=(const Array<T> &rhs) {
        if (&rhs != this)
            Array(rhs).swap(*this);
        return *this;
    }

    // move operator
    Array& operator=(Array<T> &&rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    ~Array() {
        delete[] m_array;
    }

    T& operator[](const size_t index) {
        return m_array[index];
    }

    inline T* array() const {
        return m_array;
    }

    inline size_t size() const {
        return m_size;
    }

    void swap(Array<T> &other) {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }
};
}

#endif //TULZ_ARRAY_H
