#ifndef RING_HPP
#define RING_HPP

#include <concepts>
#include <cstdint>
#include <istream>
#include <ostream>
#include <stdexcept>

#include "diophantine.hpp"

template <uint64_t> class Ring;

template <> class Ring<0> {
public:
  Ring() = delete;
  Ring(const Ring &) = delete;
  Ring &operator=(const Ring &) = delete;
};

template <uint64_t N> class Ring {
private:
  uint64_t value;
  constexpr uint64_t repr() const noexcept(true) { return value; };

public:
  explicit constexpr Ring(const std::integral auto u) { value = u % N; }
  constexpr Ring(const Ring &o) noexcept(true) { value = o.value; }

  constexpr std::ostream &operator<<(std::ostream &stream) const {
    stream << "Ring<" << N << ">(" << repr() << ")";
    return stream;
  }

  constexpr uint64_t modulus() const noexcept(true) { return N; }

  constexpr operator uint64_t() const noexcept(true) {
    return repr();
  }; // conversion op

  constexpr Ring<N> inverse() const {
    diophantine_result64_t res = diophantine(value, N, 1);
    if (res.err)
      throw std::invalid_argument(
          "Element is not invertible (gcd(value, N) != 1)");
    return Ring<N>(res.x % N);
  }

  std::istream &operator>>(std::istream &stream) {
    uint64_t input;
    stream >> input;
    value = input % N;
    return stream;
  }

  // Comparison
  constexpr bool operator==(const Ring &o) const noexcept(true) {
    return value == o.value;
  }
  constexpr bool operator!=(const Ring &o) const noexcept(true) {
    return value != o.value;
  }
  constexpr bool operator<=(const Ring &o) const noexcept(true) {
    return value <= o.value;
  }
  constexpr bool operator>=(const Ring &o) const noexcept(true) {
    return value >= o.value;
  }
  constexpr bool operator>(const Ring &o) const noexcept(true) {
    return value > o.value;
  }
  constexpr bool operator<(const Ring &o) const noexcept(true) {
    return value < o.value;
  }

  // Arithmetic
  constexpr Ring<N> operator+(const Ring &o) const noexcept(true) {
    return Ring((value % N + o.value % N) % N);
  };

  constexpr Ring<N> operator-(const Ring &o) const noexcept(true) {
    if (value >= o.value) {
      return Ring((value - o.value) % N);
    } else {
      return Ring((N - (o.value - value)) % N);
    }
  };

  constexpr Ring<N> operator*(const Ring &o) const noexcept(true) {
    return Ring((value * o.value) % N);
  }

  constexpr Ring<N> operator/(const Ring &o) const noexcept(false) {
    diophantine_result64_t res;
    res = diophantine(o.value, N, 1);
    if (res.err)
      throw std::invalid_argument("Divisor is not invertible");
    uint64_t inv = res.x;
    return Ring((value * inv) % N);
  }

  // Substitutions
  constexpr Ring<N> operator=(const Ring &o) noexcept(true) {
    value = o.value;
    return Ring(value);
  }

  constexpr Ring<N> operator+=(const Ring &o) noexcept(true) {
    value = (value % N + o.value % N) % N;
    return Ring(value);
  }

  constexpr Ring<N> operator-=(const Ring &o) noexcept(true) {
    if (value >= o.value) {
      value = (value - o.value) % N;
    } else {
      value = (N - (o.value - value)) % N;
    }
    return Ring(value);
  }

  constexpr Ring<N> operator*=(const Ring &o) noexcept(true) {
    value = (value * o.value) % N;
    return Ring(value);
  }

  constexpr Ring<N> operator/=(const Ring &o) noexcept(false) {
    diophantine_result64_t res;
    res = diophantine(o.value, N, 1);
    if (res.err)
      throw std::invalid_argument("Divisor is not invertible");
    uint64_t inv = res.x;
    value = (value * inv) % N;
    return Ring(value);
  }

  constexpr Ring<N> operator^(uint64_t exp) const noexcept(true) {
    Ring<N> res(1);
    Ring<N> base = *this;
    while (exp > 0) {
      if (exp % 2 == 1)
        res *= base;
      base *= base;
      exp /= 2;
    }
    return res;
  }
};

#endif // RING_HPP