#include <cstdint>
#include <format>
#include <print>

#include "gauss.hpp"

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

int main() {
  calc_norm();
  calc_div();
  calc_gcd();
}

void calc_norm() {
  Gauss g{a, b};
  std::println("Norm({})", g);
  std::println("-> N = {}", g.norm());
}

void calc_div() {
  Gauss x{c + a, d + b};
  Gauss y{e, f};
  Gauss q;
  Gauss r;
  std::tie(q, r) = x.div(y);
  std::println("Div({},{})", x, y);
  std::println("-> Q = {}", q);
  std::println("-> R = {}", r);
}

void calc_gcd() {
  // GCD and LCM of (a + bi, c + di, e + di)
  Gauss x{a, b};
  Gauss y{c,d};
  Gauss z{e,d};
  Gauss gcd = x.gcd_list({y,z});
  Gauss lcm = x.lcm_list({y,z});

  std::println("Array=({},{},{})", x,y,z);
  std::println("-> GCD = {}", gcd);
  std::println("-> LCM = {}", lcm);
}