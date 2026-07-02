#include <cstdint>
#include <print>
#include <queue>
#include <ranges>
#include <vector>

#include "ord.hpp"

constexpr uint64_t v[] = {2, 7, 9, 7, 6, 2};

constexpr uint64_t a = v[0];
constexpr uint64_t b = v[1];
constexpr uint64_t c = v[2];
constexpr uint64_t d = v[3];
constexpr uint64_t e = v[4];
constexpr uint64_t f = v[5];

void calc_pair();
void calc_triple();
void calc_min_A();
void calc_min_B();

int main() {
  std::println("Main for ord.hpp");
  calc_pair();
  calc_triple();
  calc_min_A();
  calc_min_B();
}

void calc_pair() {
  Prod x({a, b});
  Prod y({c, d});
  Prod z({e, f});

  std::vector<Prod> prods = {x, y, z};
  for (size_t i = 0; i < prods.size(); ++i) {
    for (size_t j = 0; j < prods.size(); ++j) {
      std::println("compare({}, {}) is {}", prods[i], prods[j],
                   compare(prods[i], prods[j]));
    }
  }
}

void calc_triple() {
  Prod x({a, c, e});
  Prod y({b, d, f});

  std::vector<Prod> prods = {x, y};
  std::println("compare({}, {}) is {}", prods[0], prods[1],
               compare(prods[0], prods[1]));
}

void calc_min_A() {
  // {(x,y) in N^2 : (x-a)^2 + (y-b)^2 < 5}
  std::vector<Prod> prods;

  auto r1 = std::views::iota(0ULL, a + 6);
  auto r2 = std::views::iota(0ULL, b + 6);

  auto cartesian = std::views::cartesian_product(r1, r2);

  for (auto &&[x, y] : cartesian) {
    if ((x - a) * (x - a) + (y - b) * (y - b) < 5) {
      prods.push_back({x, y});
    }
  }

  std::vector<Prod> mins = min_elements(prods);
  std::println("Count Min elements of A: {}", mins.size());
  std::println("Min elements of A:");
  for (const auto &p : mins) {
    std::println("{}", p);
  }
}

void calc_min_B() {
  // {(x1,x2,x3,x4) in N^4 : (x1-c)^2 + (x2-d)^2 + (x3-e)^2 + (x4-f)^2 > 224}
  std::vector<Prod> prods;
  auto r1 = std::views::iota(0ULL, c + 16);
  auto r2 = std::views::iota(0ULL, d + 16);
  auto r3 = std::views::iota(0ULL, e + 16);
  auto r4 = std::views::iota(0ULL, f + 16);

  auto cartesian = std::views::cartesian_product(r1, r2, r3, r4);

  for (auto &&[x1, x2, x3, x4] : cartesian) {
    auto dist_sq = (x1 - c) * (x1 - c) + (x2 - d) * (x2 - d) +
                   (x3 - e) * (x3 - e) + (x4 - f) * (x4 - f);
    if (dist_sq > 224) {
      prods.push_back({x1, x2, x3, x4});
    }
  }

  std::vector<Prod> mins = min_elements(prods);
  std::println("Count Min elements of B: {}", mins.size());
  std::println("Min elements of B:");
  for (const auto &p : mins) {
    std::println("{}", p);
  }
}
