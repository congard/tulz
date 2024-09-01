#ifndef TULZ_RINGBUFFER_H
#define TULZ_RINGBUFFER_H

#include <cassert>
#include <cstring>

#if defined(_MSC_VER)
#include <BaseTsd.h>
using ssize_t = SSIZE_T;
#endif

#include "RandomAccessIndexIterator.h"

namespace tulz {
/**
 * The ring buffer.
 * @tparam T The type.
 * @tparam overwrite If `true`, then in case of new element insertion
 * and if `size() == capacity()`, the old data will be overwritten.
 * Otherwise if `false`, an exception will be thrown.
 */
template<typename T, bool overwrite = false>
class RingBuffer {
public:
    using value_type = T;

    using iterator = RandomAccessIndexIterator<T, RingBuffer<T, overwrite>>;
    using const_iterator = RandomAccessIndexIterator<const T, const RingBuffer<T, overwrite>>;

public:
    explicit RingBuffer(size_t capacity)
        : m_pos(0),
          m_size(0),
          m_capacity(capacity),
          m_data(alloc(capacity)) {}

    RingBuffer(std::initializer_list<T> initializerList, size_t capacity = -1)
        : m_pos(0),
          m_size(initializerList.size()),
          m_capacity(capacity == -1 ? m_size : capacity),
          m_data(alloc(m_capacity))
    {
        size_t i = 0;

        for (auto &element : initializerList) {
            new (&m_data[i++]) T(element);
        }
    }

    RingBuffer(const RingBuffer &other) {
        *this = other;
    }

    RingBuffer& operator=(const RingBuffer &other) {
        if (this == &other)
            return *this;

        m_pos = 0;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = alloc(other.m_capacity);

        size_t i = 0;

        for (auto &element : other)
            new (&m_data[i++]) T(element);

        return *this;
    }

    RingBuffer(RingBuffer &&other) noexcept {
        *this = std::move(other);
    }

    RingBuffer& operator=(RingBuffer &&other) noexcept {
        if (this == &other)
            return *this;

        std::swap(m_pos, other.m_pos);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_data, other.m_data);

        return *this;
    }

    ~RingBuffer() {
        for (T &element : *this)
            element.~T();
        free(m_data);
    }

    T& push_back(const T &data) {
        return emplace_back(data);
    }

    T& push_front(const T &data) {
        return emplace_front(data);
    }

    template<typename ...Args>
    T& emplace_back(Args&&... args) {
        overwriteCheck();

        if (full()) {
            // overwrite: size remains unchanged, 1st element gets discarded
            m_data[m_pos] = T(std::forward<Args>(args)...);
            m_pos = modCap(m_pos + 1);
        } else {
            new (&m_data[modCap(m_pos + m_size)]) T(std::forward<Args>(args)...);
            ++m_size;
        }

        return back();
    }

    template<typename ...Args>
    T& emplace_front(Args&&... args) {
        overwriteCheck();

        m_pos = modCap(m_pos - 1);

        if (full()) {
            // overwrite: size remains unchanged, last element gets discarded
            m_data[m_pos] = T(std::forward<Args>(args)...);
        } else {
            ++m_size;
            new (&m_data[m_pos]) T(std::forward<Args>(args)...);
        }

        return front();
    }

    T pop_back() {
        notEmptyCheck();
        --m_size;
        return std::move(m_data[dataIndex(m_size)]);
    }

    T pop_front() {
        notEmptyCheck();
        auto element = std::move(m_data[m_pos]);
        m_pos = modCap(m_pos + 1);
        --m_size;
        return element;
    }

    T& front() {
        notEmptyCheck();
        return (*this)[0];
    }

    T& back() {
        notEmptyCheck();
        return (*this)[m_size - 1];
    }

    /**
     * Resizes the buffer. If `newCapacity < capacity`, the buffer
     * will shrink and extra elements will be removed if `newCapacity < size`.
     * Otherwise the capacity will be changed to `newCapacity`.
     * @param newCapacity The new size.
     * @note Addresses of the elements may change.
     */
    void resize(size_t newCapacity) {
        if (newCapacity == m_capacity)
            return;

        auto silentCopy = [this](T *dst, size_t n) {
            // copy the 1st part
            auto n1 = std::min(n, m_capacity - m_pos);
            std::memcpy(dst, m_data + m_pos, n1 * sizeof(T));

            // copy the 2nd part (if left)
            auto n2 = n - n1;
            std::memcpy(dst + n1, m_data + modCap(m_pos + n1), n2 * sizeof(T));
        };

        auto lastIndex = modCap(m_pos + static_cast<ssize_t>(m_size) - 1);

        if (m_pos <= lastIndex && lastIndex < newCapacity) {
            // just reallocate, size and pos remain unchanged
            //    |xxxoooooxxxxxxx|
            // => |xxxoooooxx|
            // => |xxxoooooxxxxxxxxxxxx|
            m_data = realloc(m_data, newCapacity);
        } else if (newCapacity < m_capacity) {
            //    |defgxxxxabc|
            // => |abcdefgx| : newCapacity = 8
            // => |abcde|    : newCapacity = 5

            // silent copy
            auto newData = alloc(newCapacity);
            auto copyCount = std::min(m_size, newCapacity);
            auto deleteCount = m_size - copyCount;

            silentCopy(newData, copyCount);

            // delete extra
            for (size_t i = 0; i < deleteCount; ++i)
                m_data[copyCount + i].~T();
            free(m_data);

            m_data = newData;
            m_size = copyCount;
            m_pos = 0;
        } else {
            //    |cdxxab|
            // => |abcdxxxx| : newCapacity = 8
            auto newData = alloc(newCapacity);
            silentCopy(newData, m_size);

            free(m_data);

            m_data = newData;
            m_pos = 0;
        }

        m_capacity = newCapacity;
    }

    const T& operator[](size_t index) const {
        return m_data[dataIndex(index)];
    }

    T& operator[](size_t index) {
        return m_data[dataIndex(index)];
    }

    template<bool _overwrite>
    bool operator==(const RingBuffer<T, _overwrite> &other) const {
        return std::equal(begin(), end(), other.begin(), other.end());
    }

    bool empty() const {
        return m_size == 0;
    }

    bool full() const {
        return m_size == m_capacity;
    }

    auto size() const {
        return m_size;
    }

    auto capacity() const {
        return m_capacity;
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

private:
    inline void overwriteCheck() const {
        // !overwrite => (m_size < m_capacity)
        assert(overwrite || m_size < m_capacity);
    }

    inline void notEmptyCheck() const {
        assert(!empty());
    }

    inline auto dataIndex(ssize_t index) const {
        return modCap(m_pos + index);
    }

    inline auto modCap(ssize_t index) const {
        // `index % capacity()` but also for negative indices
        auto a = index;
        auto b = (ssize_t) m_capacity;
        return ((a % b) + b) % b;
    }

    inline static auto alloc(size_t n) {
        return static_cast<T*>(std::malloc(n * sizeof(T)));
    }

    inline static auto realloc(T *old, size_t newSize) {
        return static_cast<T*>(std::realloc(old, newSize * sizeof(T)));
    }

    inline static void free(T *data) {
        std::free(data);
    }

private:
    ssize_t m_pos {0};
    size_t m_size {0};
    size_t m_capacity {0};
    T *m_data {nullptr};
};
}

#endif //TULZ_RINGBUFFER_H
