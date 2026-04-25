#ifndef POLY_HPP
#define POLY_HPP

#include <cstdint>
#include <format>
#include <stdexcept>
#include <vector>

class Poly {
public:
    std::vector<int64_t> c;
    
    Poly() : c{} {}
    Poly(std::vector<int64_t> coefficients) : c(coefficients) {}

    int64_t norm() {
        return c.size() - 1;
    }

    void tidy() {
        while (c.size() > 1 && c.back() == 0) {
            c.pop_back();
        }
        if (c.empty()) c.push_back(0);
    }

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
            int deg_diff = static_cast<int>(R.norm() - Y.norm());
            
            int64_t factor = R.c.back() / Y.c.back();
            
            Q.c[deg_diff] = factor;

            for (size_t i = 0; i < Y.c.size(); ++i) {
                R.c[i + deg_diff] -= factor * Y.c[i];
            }
            R.tidy();
        }

        return {Q, R};
    }

};

template <> struct std::formatter<Poly> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Poly &p, std::format_context &ctx) const {
    if (p.c.empty() || (p.c.size() == 1 && p.c[0] == 0)) {
      return std::format_to(ctx.out(), "0");
    }

    auto out = ctx.out();
    bool first = true;

    for (size_t i = p.c.size(); i-- > 0; ) {
        if (p.c[i] == 0) continue;

        if (!first) {
            if (p.c[i] > 0) out = std::format_to(out, " + ");
            else out = std::format_to(out, " - ");
        } else {
            if (p.c[i] < 0) out = std::format_to(out, "-");
            first = false;
        }

        int64_t abs_val = std::abs(p.c[i]);
        
        if (abs_val != 1 || i == 0) {
            out = std::format_to(out, "{}", abs_val);
        }

        if (i > 0) {
            out = std::format_to(out, "x");
            if (i > 1) out = std::format_to(out, "^{}", i);
        }
    }
    return out;
  }
};


#endif