#ifndef LIBJPP_H
#define LIBJPP_H

#include <cstdint>

typedef struct {
  uint64_t x;
  uint64_t y;
  bool err;
} diophantine_result64_t;

uint64_t gcd(uint64_t x, uint64_t y);
uint64_t first_prime_div(uint64_t n);
uint64_t phi(uint64_t n);
diophantine_result64_t diophantine(uint64_t a, uint64_t b, uint64_t c);

#endif