#include "libjpp.h"

uint64_t gcd(uint64_t x, uint64_t y) {
  if (y == 0)
    return x;
  if (x == 0)
    return y;
  if (x == y)
    return x;
  if (x < y)
    return gcd(y, x);

  while (y != 0) {
    uint64_t t = y;
    y = x % y;
    x = t;
  }

  return x;
}

uint64_t first_prime_div(uint64_t n) {
  if (n <= 1)
    return 0;

  for (uint64_t i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return i;
  }

  return n;
}

uint64_t phi(uint64_t n) {
  uint64_t res = 0;
  for (uint64_t i = 1; i <= n; ++i) {
    res += (gcd(i, n) == 1);
  }
  return res;
}

diophantine_result64_t diophantine(uint64_t a, uint64_t b, uint64_t c) {
  uint64_t x = 1, y = 0;
  uint64_t r = b, s = a - 1;
  uint64_t rr, ss, tmp, remainder, quotient;

  if (c % gcd(a, b) != 0) {
    diophantine_result64_t result = {.x = 0, .y = 0, .err = true};
    return result;
  }

  while (b > 0) {
    remainder = a % b;
    quotient = a / b;
    a = b;
    b = remainder;

    rr = r;
    tmp = quotient * r;
    if (x < tmp) {
      r = b * quotient;
    } else {
      r = 0;
    }
    r = r + x;
    r = r - tmp;

    ss = s;
    tmp = quotient * s;
    if (y < tmp) {
      s = a * quotient;
    } else {
      s = 0;
    }
    s = s + y;
    s = s - tmp;

    x = rr;
    y = ss;
  }

  diophantine_result64_t result = {.x = x * c, .y = y * c, .err = false};

  return result;
}