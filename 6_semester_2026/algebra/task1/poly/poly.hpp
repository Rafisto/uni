#ifndef POLY_HPP
#define POLY_HPP

#include <cmath>
#include <cstdint>
#include <format>
#include <print>
#include <stdexcept>
#include <vector>

class Poly;

struct EE {
  Poly *gcd;
  Poly *x;
  Poly *y;
};

class Poly {
public:
  std::vector<double> c;

  Poly() : c{} {}
  Poly(std::vector<double> coefficients) : c(coefficients) {}

  int64_t norm() { return c.size() - 1; }

  void tidy() {
    while (c.size() > 1 && c.back() == 0) {
      c.pop_back();
    }
    if (c.empty())
      c.push_back(0);
  }

  Poly operator+(const Poly &other) const {
    std::vector<double> res = c;
    size_t n = other.c.size();
    if (res.size() < n)
      res.resize(n, 0.0);

    for (size_t i = 0; i < n; ++i) {
      res[i] += other.c[i];
    }
    return Poly(res);
  }

  Poly operator-(const Poly &other) const {
    std::vector<double> res = c;
    size_t n = other.c.size();
    if (res.size() < n)
      res.resize(n, 0.0);

    for (size_t i = 0; i < n; ++i) {
      res[i] -= other.c[i];
    }
    return Poly(res);
  }

  Poly operator*(const Poly &other) const {
    if (is_zero() || other.is_zero())
      return Poly({0.0});

    std::vector<double> res(c.size() + other.c.size() - 1, 0.0);
    for (size_t i = 0; i < c.size(); ++i) {
      for (size_t j = 0; j < other.c.size(); ++j) {
        res[i + j] += c[i] * other.c[j];
      }
    }
    return Poly(res);
  }

  bool is_zero() const { return c.size() == 1 && std::abs(c[0]) < 1e-6; }

  // X=QY+R, Q - Quotient, R - Remainder
  // Euclidean Algorithm provided the norm decreases
  std::pair<Poly, Poly> div(Poly &Y) {
    if (Y.c.size() == 1 && Y.c[0] == 0) {
      throw std::invalid_argument("Divisor is 0");
    }

    Poly R = *this;
    Poly Q;

    if (R.norm() < Y.norm()) {
      Q.c = {0};
      return {Q, R};
    }

    Q.c.resize(R.norm() - Y.norm() + 1, 0);

    while (R.norm() >= Y.norm() && !(R.c.size() == 1 && R.c[0] == 0)) {
      int64_t deg_diff = R.norm() - Y.norm();

      double factor = R.c.back() / Y.c.back();

      Q.c[deg_diff] = factor;

      for (size_t i = 0; i < Y.c.size(); ++i) {
        R.c[i + deg_diff] -= factor * Y.c[i];
      }
      R.tidy();
    }

    return {Q, R};
  }

  // GCD(A,B)
  Poly gcd(Poly A, Poly B) {
    while (B.norm() > 0 || (B.norm() == 0 && std::abs(B.c[0]) > 1e-4)) {
        auto [_, r] = A.div(B);
        A = B;
        B = r;
        if (B.is_zero()) break;
    }

    A.tidy();
    if (!A.is_zero()) {
      double lead = A.c.back();
      for (double &coeff : A.c) {
        coeff /= lead;
      }
    }

    return A;
  }

  // LCM(A,B) = (A*B)/GCD(A,B)
  Poly lcm(Poly A, Poly B) {
    if (A.is_zero() || B.is_zero())
      return Poly({0.0});
    Poly g = gcd(A, B);
    return (A * B).div(g).first;
  }

  // AX+BY=GCD(A,B), Returns GCD, X, Y
  EE extended_gcd(Poly A, Poly B) {
    Poly s = {{0}}, old_s = {{1}};
    Poly t = {{1}}, old_t = {{0}};
    Poly r = B, old_r = A;

    while (!(r.c.size() == 1 && r.c[0] == 0)) {
      auto [quotient, remainder] = old_r.div(r);

      old_r = r;
      r = remainder;

      Poly temp_s = s;
      s = old_s - (quotient * s);
      old_s = temp_s;

      Poly temp_t = t;
      t = old_t - (quotient * t);
      old_t = temp_t;
    }

    old_r.tidy();
    if (!old_r.is_zero()) {
      double lead = old_r.c.back();
      for (double &coeff : old_r.c) {
        coeff /= lead;
      }
    }

    return {.gcd = new Poly(old_r), .x = new Poly(old_s), .y = new Poly(old_t)};
  };

  double evaluate(double x) const {
    double result = 0.0;
    double power = 1.0;

    for (double coeff : c) {
      result += coeff * power;
      power *= x;
    }
    return result;
  }

  double bisection_root(double a, double b, double tol = 1e-9) {
    if (a > 0 || b < 0) {
      throw std::invalid_argument(
          "Function values at the endpoints must have opposite signs.");
    }

    while (b - a > tol) {
      double mid = (a + b) / 2;
      double f_mid = evaluate(mid);

      if (std::abs(f_mid) < tol) {
        return mid;
      } else if (f_mid > 0) {
        b = mid;
      } else {
        a = mid;
      }
    }
    return (a + b) / 2;
  }

  // Find const_sub_to_gcd, st. GCD(v,w)=1 then GCD(v,w+g) != 1
  Poly const_sub_to_gcd(Poly w) {
    double v_root = bisection_root(-1e6, 1e6);
    std::println("Root of v: {}", v_root);
    double w_at_root = w.evaluate(v_root);
    std::println("w at root of v: {}", w_at_root);
    Poly g{{-w_at_root}};
    return w + g;
  };
};

template <> struct std::formatter<Poly> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Poly &p, std::format_context &ctx) const {
    if (p.c.empty() || (p.c.size() == 1 && p.c[0] == 0)) {
      return std::format_to(ctx.out(), "0");
    }

    auto out = ctx.out();
    bool first = true;

    for (size_t i = p.c.size(); i-- > 0;) {
      if (p.c[i] == 0)
        continue;

      if (!first) {
        if (p.c[i] > 0)
          out = std::format_to(out, " + ");
        else
          out = std::format_to(out, " - ");
      } else {
        if (p.c[i] < 0)
          out = std::format_to(out, "-");
        first = false;
      }

      double abs_val = std::abs(p.c[i]);
      // abs_val = std::ceil(abs_val * 100.0) / 100.0;

      if (abs_val != 1 || i == 0) {
        out = std::format_to(out, "{}", abs_val);
      }

      if (i > 0) {
        out = std::format_to(out, "x");
        if (i > 1)
          out = std::format_to(out, "^{}", i);
      }
    }
    return out;
  }
};

#endif