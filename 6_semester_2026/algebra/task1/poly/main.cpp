#include <print>

#include "poly.hpp"

constexpr int64_t v[] = {2, 7, 9, 7, 6, 2};

constexpr int64_t a = v[0];
constexpr int64_t b = v[1];
constexpr int64_t c = v[2];
// constexpr int64_t d = v[3];
// constexpr int64_t e = v[4];
// constexpr int64_t f = v[5];

void calc_norm();
void calc_div();

int main() {
  std::println("Main for poly.hpp");
  calc_norm();
  calc_div();
}

void calc_norm() {
  Poly x{};
  x.c.resize(a + 1);
  x.c[a] = c;
  x.c[0] = b;
  x.tidy();

  std::println("Norm({})", x);
  std::println("{}", x.norm());
}

void calc_div() {
  Poly x{};
  x.c.resize(a + 1);
  x.c[a] = c;
  x.c[0] = b;
  x.tidy();

  Poly y{{1, 1}};

  Poly q;
  Poly r;
  std::tie(q, r) = x.div(y);

  std::println("Div({};{})", x, y);
  std::println("Q = {}", q);
  std::println("R = {}", r);
}