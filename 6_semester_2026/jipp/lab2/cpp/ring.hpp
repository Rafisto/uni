#ifndef RING_HPP
#define RING_HPP

#include <cstdint>

template <uint64_t N> class Ring {
private:
  uint64_t value;

public:
  Ring(const uint64_t u) { value = u % N; }

  uint64_t repr() { return value; };

  // Comparison
  bool operator==(const Ring &o);
  bool operator!=(const Ring &o);
  bool operator<=(const Ring &o);
  bool operator>=(const Ring &o);
  bool operator>(const Ring &o);
  bool operator<(const Ring &o);

  // Arithmetic
  Ring operator+(const Ring &o);
  Ring operator-(const Ring &o);
  Ring operator*(const Ring &o);
  Ring operator/(const Ring &o) noexcept(false);

  // Substitutions
  Ring operator=(const Ring &o);
  Ring operator+=(const Ring &o);
  Ring operator-=(const Ring &o);
  Ring operator*=(const Ring &o);
  Ring operator/=(const Ring &o) noexcept(false);
};

#endif // RING_HPP