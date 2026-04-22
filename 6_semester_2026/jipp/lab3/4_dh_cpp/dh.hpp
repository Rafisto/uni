#ifndef RSA_HPP
#define RSA_HPP

#include <random>
#include <stdexcept>

#include "diophantine.hpp"

template <typename T> class DHSetup {
private:
  T g;

public:
  DHSetup() : g(1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    g = T::g();
  }

  T getGenerator() const { return g; }
  T power(T a, uint64_t b) const { return a ^ b; }

  T getPublicKey() const { return g; }
  void setPublicKey(T new_g) { g = new_g; }

  T encrypt(T m) const { return m ^ g; }
  T decrypt(T s) const {
    diophantine_result64_t res = diophantine(g, s, 1);
    if (res.err) {
      throw std::runtime_error("unexpected gcd(g, s) != 1");
    }
    return s ^ res.x;
  }
};

#endif