#include <print>
#include "polyreduce.hpp"

int main() {
    // f = x^3 - x^2*y - x^2*z
    poly_t poly{
        {{3,0,0},{1}},
        {{2,1,0},{-1}},
        {{2,0,1},{-1}}
    };

    poly_t g1{
        {{2,1,0},{1}},
        {{0,0,1},{-1}},
    };

    poly_t g2{
        {{1,1,0},{1}},
        {{0,0,0},{-1}},
    };

    std::vector<poly_t> g12 {g1,g2};
    std::vector<poly_t> g21 {g2,g1};

    auto [q12, r12] = poly_reduce(poly, g12, compare_graded_lex);
    auto [q21, r21] = poly_reduce(poly, g21, compare_graded_lex);

    std::println("r1={}", poly_fmt(r12, compare_lex));
    for (size_t p = 0; p < q12.size(); ++p) {
        std::println("a(g{}) = {}", p, poly_fmt(q12[p], compare_lex));
    }

    std::println("r2={}", poly_fmt(r21, compare_lex));
        for (size_t p = 0; p < q21.size(); ++p) {
        std::println("a(g{}) = {}", p, poly_fmt(q21[p], compare_lex));
    }
}
