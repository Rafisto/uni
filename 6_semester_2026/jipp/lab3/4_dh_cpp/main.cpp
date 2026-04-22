#include <cassert>
#include <clocale>

#include "diophantine.hpp"
#include "power.hpp"
#include "ring.hpp"
#include "dh.hpp"

int main() {
  constexpr uint64_t n = 1234567891;
  using R = Ring<n>;
  DHSetup<R> dh{};

  uint64_t a = 12345;
  uint64_t b = 54321;

  R A = dh.power(dh.getGenerator(), a);
  R B = dh.power(dh.getGenerator(), b);

  assert(dh.power(B, a) == dh.power(A, b ));

  return 0;
}