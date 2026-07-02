#ifndef LIBJPP_H
#define LIBJPP_H

#include <stdbool.h>
#include <stdint.h>

// Due to the lack of Result Functor in C/Ada
// Go-like Structure is introduced
// if s.err != nil ->
typedef struct {
  uint64_t x;
  uint64_t y;
  bool err;
} diophantine_result64_t;

// Greatest Common Divisor
// gcd(x,y)
uint64_t gcd(uint64_t x, uint64_t y);

// First Prime Divisor of n
// p : p | n, p prime, not exists q < a : q prime, q | n
uint64_t first_prime_div(uint64_t n);

// Euler Totient Function
// phi(n)
uint64_t phi(uint64_t n);

// Diophantine over natural numbers (via Extended Euclidean Algorithm)
// ax - by = c
diophantine_result64_t diophantine(uint64_t a, uint64_t b, uint64_t c);

#endif