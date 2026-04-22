#ifndef RSA_HPP
#define RSA_HPP

#include <random>
#include <stdexcept>

#include "diophantine.hpp"

template <typename T> class RSA {
private:
  T e;
  uint64_t d;
  uint64_t n;

public:
  RSA(uint64_t p, uint64_t q) : e(1) {
    n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(2, phi - 1);

    uint64_t temp_e = 1;
    do {
      temp_e = dist(gen);
    } while (gcd(temp_e, phi) != 1);
    e = T(temp_e);

    diophantine_result64_t res = diophantine(temp_e, phi, 1);
    if (res.err) {
      throw std::runtime_error("unexpected gcd(e, phi) != 1");
    }

    d = res.x;
  }

  unsigned getModulo() const { return static_cast<unsigned>(n); }

  T getPublicKey() const { return e; }

  T encrypt(T m) const { return m ^ e; }

  T decrypt(T s) const { return s ^ d; }
};

#endif