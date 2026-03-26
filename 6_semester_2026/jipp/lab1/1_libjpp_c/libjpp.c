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

// ax - by = c
diophantine_result64_t diophantine(uint64_t m, uint64_t n, uint64_t z) {
  diophantine_result64_t result = {.x = 0, .y = 0, .err = true};
  if (gcd(m, n) != z) return result;
  uint64_t a = m, b = n, x = 1, y = 0, r = n, s = m - 1;
  uint64_t rr, ss, rem, quot, tmp;

  while (b > 0) {
    rem = a % b;
    quot = a / b;
    a = b;
    b = rem;
    rr = r;
    tmp = quot * r;
    if (x < tmp)
      r = n * quot;
    else
      r = 0;

    r = r + x;
    r = r - tmp;
    ss = s;
    tmp = quot * s;
    if (y < tmp)
      s = m * quot;
    else
      s = 0;
    s = s + y;
    s = s - tmp;
    x = rr;
    y = ss;
  }
  
  result.x = x;
  result.y = y;
  result.err = false;
  return result;
}