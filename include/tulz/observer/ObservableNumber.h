#ifndef TULZ_OBSERVABLENUMBER_H
#define TULZ_OBSERVABLENUMBER_H

#include "Observable.h"

namespace tulz {
template<typename T>
class ObservableNumber: public Observable<T> {
public:
    using Observable<T>::Observable;
    using Observable<T>::operator=;
    using Observable<T>::operator*;

    // postfix increment
    T operator++(int) {
        auto prev = this->m_val;
        ++this->m_val;
        this->notify();
        return prev;
    }

    // prefix increment
    T operator++() {
        ++this->m_val;
        this->notify();
        return this->m_val;
    }

    ObservableNumber& operator+=(T other) {
        this->m_val += other;
        this->notify();
        return *this;
    }

    // postfix decrement
    T operator--(int) {
        auto prev = this->m_val;
        --this->m_val;
        this->notify();
        return prev;
    }

    // prefix decrement
    T operator--() {
        --this->m_val;
        this->notify();
        return this->m_val;
    }

    ObservableNumber& operator-=(T other) {
        this->m_val -= other;
        this->notify();
        return *this;
    }

    ObservableNumber& operator*=(T other) {
        this->m_val *= other;
        this->notify();
        return *this;
    }

    ObservableNumber& operator/=(T other) {
        this->m_val /= other;
        this->notify();
        return *this;
    }
};

using ObservableChar = ObservableNumber<char>;
using ObservableUChar = ObservableNumber<unsigned char>;
using ObservableShort = ObservableNumber<short>;
using ObservableUShort = ObservableNumber<unsigned short>;
using ObservableInt = ObservableNumber<int>;
using ObservableUInt = ObservableNumber<unsigned int>;
using ObservableLong = ObservableNumber<long>;
using ObservableULong = ObservableNumber<unsigned long>;
using ObservableFloat = ObservableNumber<float>;
using ObservableDouble = ObservableNumber<double>;
}

#endif //TULZ_OBSERVABLENUMBER_H
