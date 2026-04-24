#ifndef DH_HPP
#define DH_HPP

#include <cstdint>

template <typename T> class DHSetup {
private:
  T g;

public:
  DHSetup() : g(T::g()) {}

  T getGenerator() const { return g; }

  T power(T a, uint64_t b) const {
    T result = T(1);
    while (b > 0) {
      if (b % 2 == 1)
        result = result * a;
      a = a * a;
      b >>= 1;
    }
    return result;
  }
};

#endif