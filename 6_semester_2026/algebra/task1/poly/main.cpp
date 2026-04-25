#include <print>

#include "poly.hpp"

constexpr int64_t v[] = {2, 7, 9, 7, 6, 2};

constexpr int64_t a = v[0];
constexpr int64_t b = v[1];
constexpr int64_t c = v[2];
constexpr int64_t d = v[3];
constexpr int64_t e = v[4];
constexpr int64_t f = v[5];

void calc_norm();
void calc_div();
void calc_gcd();
void calc_ee();

int main() {
  std::println("Main for poly.hpp");
  calc_norm();
  calc_div();
  calc_gcd();
  calc_ee();
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

void calc_gcd() {
  Poly X{};
  X.c.resize(4);
  X.c[3] = a;
  X.c[2] = b;
  X.c[1] = c;
  X.c[0] = d;
  X.tidy();

  Poly Y{};
  Y.c.resize(4);
  Y.c[3] = d;
  Y.c[2] = e;
  Y.c[1] = f;
  Y.tidy();

  Poly g = X.gcd(X, Y);
  std::println("GCD({}, {})", X, Y);
  std::println("GCD = {}", g);
}

void calc_ee() {
  Poly V{};
  V.c.resize(4);
  V.c[3] = a;
  V.c[2] = b;
  V.c[1] = c;
  V.c[0] = d;
  V.tidy();

  Poly W{};
  W.c.resize(4);
  W.c[3] = d;
  W.c[2] = e;
  W.c[1] = f;
  W.tidy();

  // vV + wW = GCD(V,W)
  auto [gcd, v,w] = V.extended_gcd(V, W);
  std::println("Extended GCD({}, {})", V, W);
  std::println("GCD = {}", *gcd);
  std::println("v = {}", *v);
  std::println("w = {}", *w);

  W = V.const_sub_to_gcd(W);

  Poly p = V.lcm(V,W);
  std::println("LCM({}, {})", V, W);
  std::println("LCM = {}", p);
}
