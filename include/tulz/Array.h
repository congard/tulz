#ifndef TULZ_ARRAY_H
#define TULZ_ARRAY_H

#include <cstddef>
#include <cstring>
#include <algorithm>

namespace tulz {

/**
 * Container for C array
 * @tparam T
 */
template <typename T>
class Array {
public:
    using value_type = T;

    T *m_array = nullptr;
    size_t m_size = 0;

    Array(T *array, size_t size, bool copy = true) {
        if (copy) {
            m_array = static_cast<T*>(malloc(size * sizeof(T)));
            memcpy(m_array, array, size * sizeof(T));
        } else { // Warning: dangerous since we don't know how array was created
            m_array = array;
        }

        m_size = size;
    }

    explicit Array(size_t size) {
        m_size = size;
        m_array = static_cast<T*>(malloc(size * sizeof(T)));
    }

    Array(size_t size, const T &value): Array(size) {
        for (size_t i = 0; i < size; ++i) {
            m_array[i] = value;
        }
    }

    Array() = default;

    // copy constructor
    Array(const Array<T> &src) {
        m_size = src.m_size;
        m_array = static_cast<T*>(malloc(m_size * sizeof(T)));

        for (size_t i = 0; i < m_size; i++) {
            m_array[i] = src.m_array[i];
        }
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
        free(m_array);
    }

    T& operator[](size_t index) {
        return m_array[index];
    }

    const T& operator[](size_t index) const {
        return m_array[index];
    }

    void resize(size_t size) {
        m_array = static_cast<T*>(realloc(m_array, size * sizeof(T)));
        m_size = size;
    }

    void resize(size_t size, const T &value) {
        m_array = static_cast<T*>(realloc(m_array, size * sizeof(T)));

        if (size > m_size) {
            for (size_t i = m_size; i < size; ++i) {
                m_array[i] = value;
            }
        }

        m_size = size;
    }

    T* array() const {
        return m_array;
    }

    size_t size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

    void swap(Array<T> &other) {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }
};
}

#endif //TULZ_ARRAY_H
