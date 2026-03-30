#ifndef RING_HPP
#define RING_HPP

#include <cstdint>

template <uint64_t N>
class Ring {
    uint64_t value;

    Ring(const uint64_t u) {
        value = u;
    }
    
    Ring operator+(const Ring &o) {
        return Ring((value + o) % N);
    }

    Ring operator-(const Ring &o) {
        return Ring((value - o) % N);
    }

    Ring operator*(const Ring &o) {
        return Ring((value * o) % N);
    }

    Ring operator/(const Ring &o) {
        // use value * o^{-1}, because it may not exist
        return Ring((value / o) % N);
    }
};

#endif // RING_HPP