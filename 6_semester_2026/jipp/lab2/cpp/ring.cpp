#include "ring.hpp"
#include "libjpp.hpp"
#include <exception>
#include <stdexcept>

template <uint64_t N>
Ring<N> Ring<N>::operator+(const Ring &o) {
    return Ring((value % N + o.value % N) % N);
};

template <uint64_t N>
Ring<N> Ring<N>::operator-(const Ring &o) {
    if (value >= o.value) {
        return Ring((value - o.value) % N);
    } else {
        return Ring((N - (o.value - value)) % N);
    }
};

template <uint64_t N>
Ring<N> Ring<N>::operator*(const Ring &o) {
    return Ring((value * o.value) % N);
}


template <uint64_t N>
Ring<N> Ring<N>::operator/(const Ring &o) noexcept(false) {
    diophantine_result64_t res;
    res = diophantine(o.value,N,1);
    if (res.err) throw std::invalid_argument("Divisor is not invertible");
    uint64_t inv = res.x;
    return Ring((value * inv) % N);
}

template <uint64_t N>
bool Ring<N>::operator==(const Ring &o) {
    return value == o.value;
}

template <uint64_t N>
bool Ring<N>::operator!=(const Ring &o) {
    return value != o.value;    
}

template <uint64_t N>
bool Ring<N>::operator<=(const Ring &o) {
    return value <= o.value;    
}

template <uint64_t N>
bool Ring<N>::operator>=(const Ring &o) {
    return value >= o.value;
}

template <uint64_t N>
bool Ring<N>::operator>(const Ring &o) {
    return value > o.value;
}

template <uint64_t N>
bool Ring<N>::operator<(const Ring &o) {
    return value < o.value;
}

template <uint64_t N>
Ring<N> Ring<N>::operator=(const Ring &o) {
    value = o.value;
    return Ring(value);
}

template <uint64_t N>
Ring<N> Ring<N>::operator+=(const Ring &o) {
    value = (value % N + o.value % N) % N;
    return Ring(value);
}

template <uint64_t N>
Ring<N> Ring<N>::operator-=(const Ring &o) {
    if (value >= o.value) {
        value = (value - o.value) % N;
    } else {
        value = (N - (o.value - value)) % N;
    }
    return Ring(value);
}

template <uint64_t N>
Ring<N> Ring<N>::operator*=(const Ring &o) {
    value = (value * o.value) % N;
    return Ring(value);
}

template <uint64_t N>
Ring<N> Ring<N>::operator/=(const Ring &o) noexcept(false) {
    diophantine_result64_t res;
    res = diophantine(o.value,N,1);
    if (res.err) throw std::invalid_argument("Divisor is not invertible");
    uint64_t inv = res.x;
    value = (value * inv) % N;
    return Ring(value);
}

template class Ring<15>;
template class Ring<17>;