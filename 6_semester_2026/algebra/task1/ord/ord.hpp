#ifndef ORD_HPP
#define ORD_HPP

#include <cstdint>
#include <format>
#include <vector>

// N^n, n >= 1
enum CmpResult { LEQ, EQ, GEQ, FAIL };

typedef std::vector<uint64_t> Prod;

// product ordering: x <= y iff x_i <= y_i for all i
inline CmpResult compare(const Prod &x, const Prod &y) {
  if (x.size() != y.size()) {
    throw std::invalid_argument("must be of the same size");
  }

  if (x == y) {
    return EQ;
  }

  // check <=
  bool all_leq = true;
  for (size_t i = 0; i < x.size(); ++i) {
    if (x[i] > y[i]) {
      all_leq = false;
      break;
    }
  }

  bool all_geq = true;
  for (size_t i = 0; i < x.size(); ++i) {
    if (x[i] < y[i]) {
      all_geq = false;
      break;
    }
  }

  if (all_leq) {
    return LEQ;
  } else if (all_geq) { 
    return GEQ;
  } else {
    return FAIL;
  }
}

inline std::vector<Prod> min_elements(const std::vector<Prod> &prods) {
    if (prods.empty()) return {};

    std::vector<Prod> mins;

    for (const auto &p : prods) {
        bool is_min = true;
        
        for (auto it = mins.begin(); it != mins.end(); ) {
            CmpResult result = compare(p, *it);

            if (result == LEQ) {
                it = mins.erase(it);
            } else if (compare(*it, p) == LEQ) {
                is_min = false;
                break;
            } else {
                ++it;
            }
        }

        if (is_min) {
            mins.push_back(p);
        }
    }

    return mins;
}

template <> struct std::formatter<CmpResult> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const CmpResult &g, std::format_context &ctx) const {
    switch (g) {
    case LEQ:
      return std::format_to(ctx.out(), "<=");
    case EQ:
      return std::format_to(ctx.out(), "==");
    case GEQ:
      return std::format_to(ctx.out(), ">=");
    case FAIL:
      return std::format_to(ctx.out(), "no comparison possible");
    }
  };
};

#endif