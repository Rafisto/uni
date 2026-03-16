#ifndef LIBJPP_H
#define LIBJPP_H

#include <stdint.h>

typedef struct {
    uint64_t x;
    uint64_t y;
} pair64_t;

uint64_t gcd(uint64_t x, uint64_t y); // gcd(x,y)
uint64_t first_prime_div(uint64_t n); // p : p | n, p prime, not exists q < a : q prime, q | n
uint64_t phi(uint64_t n); // phi(n)
pair64_t diophantine(uint64_t a, uint64_t b, uint64_t c); // ax - by = c

#endif