#ifndef TULZ_RANDOMACCESSINDEXITERATOR_H
#define TULZ_RANDOMACCESSINDEXITERATOR_H

#include <iterator>

namespace tulz {
template<typename Type, typename Container>
class RandomAccessIndexIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    explicit RandomAccessIndexIterator(Container &container, size_t index = 0)
        : m_container(container), m_index(index) {}

    // Prefix increment
    RandomAccessIndexIterator& operator++() {
        ++m_index;
        return *this;
    }

    // Prefix decrement
    RandomAccessIndexIterator& operator--() {
        --m_index;
        return *this;
    }

    // Postfix increment
    const RandomAccessIndexIterator operator++(int) {
        RandomAccessIndexIterator it = *this;
        ++(*this);
        return it;
    }

    // Postfix decrement
    const RandomAccessIndexIterator operator--(int) {
        RandomAccessIndexIterator it = *this;
        --(*this);
        return it;
    }

    RandomAccessIndexIterator& operator+=(difference_type i) {
        m_index += i;
        return *this;
    }

    RandomAccessIndexIterator& operator-=(difference_type i) {
        m_index -= i;
        return *this;
    }

    RandomAccessIndexIterator operator+(difference_type i) {
        RandomAccessIndexIterator it = *this;
        it += i;
        return it;
    }

    RandomAccessIndexIterator operator-(difference_type i) {
        RandomAccessIndexIterator it = *this;
        it -= i;
        return it;
    }

    difference_type operator-(RandomAccessIndexIterator other) {
        return m_index - other.m_index;
    }

    bool operator==(RandomAccessIndexIterator other) const {
        return m_index == other.m_index;
    }

    bool operator!=(RandomAccessIndexIterator other) const {
        return !(*this == other);
    }

    bool operator<(RandomAccessIndexIterator other) const {
        return m_index < other.m_index;
    }

    bool operator>(RandomAccessIndexIterator other) const {
        return m_index > other.m_index;
    }

    bool operator<=(RandomAccessIndexIterator other) const {
        return m_index <= other.m_index;
    }

    bool operator>=(RandomAccessIndexIterator other) const {
        return m_index >= other.m_index;
    }

    reference operator*() const {
        return m_container[m_index];
    }

private:
    Container &m_container;
    size_t m_index;
};
}

#endif //TULZ_RANDOMACCESSINDEXITERATOR_H
