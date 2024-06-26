#ifndef TULZ_ARRAY_H
#define TULZ_ARRAY_H

#include <cstddef>
#include <cstring>
#include <algorithm>
#include <initializer_list>

#include "RandomAccessIndexIterator.h"

namespace tulz {
/**
 * Container for C array
 * @tparam T
 */
template <typename T>
class Array {
public:
    using iterator = RandomAccessIndexIterator<T, Array<T>>;
    using const_iterator = RandomAccessIndexIterator<const T, const Array<T>>;

public:
    using value_type = T;

    T *m_array = nullptr;
    size_t m_size = 0;

    Array(T *array, size_t size, bool copy = true) {
        if (copy) {
            if constexpr (!std::is_class_v<T>) {
                m_array = static_cast<T *>(malloc(size * sizeof(T)));
                memcpy(m_array, array, size * sizeof(T));
            } else {
                m_array = static_cast<T*>(malloc(m_size * sizeof(T)));

                for (size_t i = 0; i < m_size; i++) {
                    new (&m_array[i]) T(array[i]);
                }
            }
        } else { // Warning: dangerous since we don't know how the array was created
            m_array = array;
        }

        m_size = size;
    }

    Array(std::initializer_list<T> initializerList) {
        m_size = initializerList.size();
        m_array = static_cast<T*>(malloc(m_size * sizeof(T)));

        size_t i = 0;

        for (const T &e : initializerList) {
            new (&m_array[i++]) T(std::move(e));
        }
    }

    explicit Array(size_t size) {
        m_size = size;
        m_array = static_cast<T*>(malloc(size * sizeof(T)));
        initialize(0, size);
    }

    Array(size_t size, const T &value) {
        m_size = size;
        m_array = static_cast<T*>(malloc(size * sizeof(T)));

        for (size_t i = 0; i < size; ++i) {
            new (&m_array[i]) T(value);
        }
    }

    Array() = default;

    // copy constructor
    Array(const Array<T> &src) {
        m_size = src.m_size;
        m_array = static_cast<T*>(malloc(m_size * sizeof(T)));

        if constexpr (!std::is_class_v<T>) {
            memcpy(m_array, src.m_array, m_size * sizeof(T));
        } else {
            for (size_t i = 0; i < m_size; i++) {
                new (&m_array[i]) T(src.m_array[i]);
            }
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
        destroy(0, m_size);
        free(m_array);
    }

    T& operator[](size_t index) {
        return m_array[index];
    }

    const T& operator[](size_t index) const {
        return m_array[index];
    }

    void resize(size_t size) {
        destroy(size, m_size);

        m_array = static_cast<T*>(realloc(m_array, size * sizeof(T)));

        if (size > m_size)
            initialize(m_size, size);

        m_size = size;
    }

    void resize(size_t size, const T &value) {
        destroy(size, m_size);

        m_array = static_cast<T*>(realloc(m_array, size * sizeof(T)));

        if (size > m_size) {
            for (size_t i = m_size; i < size; ++i) {
                new (&m_array[i]) T(value);
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

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, size());
    }

    const_iterator begin() const {
        return const_iterator(*this, 0);
    }

    const_iterator end() const {
        return const_iterator(*this, size());
    }

    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }

    T& front() noexcept {
        return m_array[0];
    }

    T& back() noexcept {
        return m_array[m_size - 1];
    }

    void swap(Array<T> &other) {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }

private:
    void initialize(size_t begin, size_t end) {
        if constexpr (!std::is_class_v<T>)
            return;

        for (size_t i = begin; i < end; ++i) {
            new (&m_array[i]) T();
        }
    }

    void destroy(size_t begin, size_t end) {
        if constexpr (!std::is_class_v<T>)
            return;

        for (size_t i = begin; i < end; ++i) {
            m_array[i].~T();
        }
    }
};
}

#endif //TULZ_ARRAY_H
