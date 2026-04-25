#ifndef GAUSS_RING
#define GAUSS_RING

#include <cmath>
#include <cstdint>
#include <format>
#include <utility>
#include <vector>

class Gauss {
public:
  int64_t real;
  int64_t imaginary;
  Gauss() : real(0), imaginary(0) {}
  Gauss(int64_t r, int64_t i) : real(r), imaginary(i) {}

  // N(a+bi) = (a+bi)(a-bi) = a^2 + b^2 is the norm
  int64_t norm() { return real * real + imaginary * imaginary; }

  static int64_t round_div(int64_t n, int64_t d) {
    return std::llround((double)n / d);
  }

  // X + Y = (a+bi) + (c+di) = (a+c) + i(b+d)
  Gauss operator+(const Gauss &other) const {
    return Gauss(real + other.real, imaginary + other.imaginary);
  }

  // X - Y = (a+bi) - (c+di) = (a-c) + i(b-d)
  Gauss operator-(const Gauss &other) const {
    return Gauss(real - other.real, imaginary - other.imaginary);
  }

  // X + Y = (a+bi) * (c+di) = (ac - bd) + i(ad + bc)
  Gauss operator*(const Gauss &other) const {
    return Gauss(real * other.real - imaginary * other.imaginary,
                 real * other.imaginary + imaginary * other.real);
  }

  // Div (X,Y) = (Q,R), Q - Quotient, R - Remainder
  std::pair<Gauss, Gauss> div(Gauss &Y) {
    int64_t a = real;
    int64_t b = imaginary;
    int64_t c = Y.real;
    int64_t d = Y.imaginary;

    // X = QY + R
    // X/Y = (a+bi)/(c+di) * (c-di)/(c-di) = (ac+bd)/N(y) + i (bc-ad)/N(y)

    // Quotient
    // Q = round((ac-bd)/N(y)) + i round((bc-ad)/N(y))
    int64_t N = Y.norm();
    int64_t e = round_div((a * c + b * d), N);
    int64_t f = round_div((b * c - a * d), N);

    // Remainder
    // R = (g + hi) = X - QY = a + bi - (e + fi)(c + di) =
    // = a + bi - (ec + edi + cfi - fd) =
    // = a + bi - ec - edi - cfi + fd =
    // = (a-ec+fd) + (b-ed-cf)i
    int64_t g = a - e * c + f * d;
    int64_t h = b - e * d - c * f;

    return {Gauss(e, f), Gauss(g, h)};
  };

  // euclidean algorithm
  Gauss gcd(Gauss a, Gauss b) {
    while (b.norm() != 0) {
      // Q = .first, R = .second
      Gauss r = a.div(b).second;
      a = b;
      b = r;
    }
    return a;
  }

  // lcm(a, b) = a*b / gcd(a, b)
  Gauss lcm(Gauss a, Gauss b) {
    if (a.norm() == 0 || b.norm() == 0) {
      return Gauss(0, 0);
    }
    Gauss common = gcd(a, b);
    // Q = .first, R = .second
    Gauss quotient = a.div(common).first;
    return quotient * b;
  }

  Gauss gcd_list(const std::vector<Gauss> &v) {
    if (v.empty())
      return Gauss(0, 0);
    if (v.size() == 1)
      return v[0];

    Gauss result = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
      result = gcd(result, v[i]);
    }
    return result;
  }

  Gauss lcm_list(const std::vector<Gauss> &v) {
    if (v.empty())
      return Gauss(0, 0);
    if (v.size() == 1)
      return v[0];

    Gauss result = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
      result = lcm(result, v[i]);
    }
    return result;
  }
};

template <> struct std::formatter<Gauss> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Gauss &g, std::format_context &ctx) const {
    if (g.imaginary < 0) {
      return std::format_to(ctx.out(), "{}-{}i", g.real, g.imaginary * -1);
    } else {
      return std::format_to(ctx.out(), "{}+{}i", g.real, g.imaginary);
    }
  };
};

#endif