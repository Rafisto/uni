#include <print>
#include "polyreduce.hpp"

int main() {
    // h(x,y,z) = x^2 y^7 - y^9 z^7 + x^6 z^2
    poly_t poly{
        {{2,7,0}, 1},
        {{0,9,7}, -1},
        {{6,0,2}, 1}
    };

    std::print("Formatted polynomial: {}\n", poly_fmt(poly, compare_graded_lex));

    poly_t g1 = {{{3, 0, 0}, 1}, {{0, 0, 1}, 1}};
    poly_t g2 = {{{0, 0, 3}, 1}, {{1,0, 0}, 1}};
    poly_t g3 = {{{0, 3, 0}, 1}, {{1, 0, 1}, 1}};

    std::print("g1: {}\n", poly_fmt(g1, compare_lex));
    std::print("g2: {}\n", poly_fmt(g2, compare_lex));
    std::print("g3: {}\n", poly_fmt(g3, compare_lex));

    std::vector<poly_t> G{g1, g2, g3};

    // 1. Lex order
    auto [quotients, remainder] = poly_reduce(poly, G, compare_lex);
    std::print("Remainder (lex): {}\n", poly_fmt(remainder, compare_lex));
    for (size_t p = 0; p < quotients.size(); ++p) {
        std::print("a(g{}) = {}\n", p, poly_fmt(quotients[p], compare_lex));
    }

    // 2. Ordered lex
    std::vector<size_t> pi{2, 1,0}; 
    g_pi = pi;
    auto [quotients_ordered, remainder_ordered] = poly_reduce(poly, G, compare_ordered_wrapper);
    std::print("Remainder (ordered lex): {}\n", poly_fmt(remainder_ordered, compare_lex));
    for (size_t p = 0; p < quotients_ordered.size(); ++p) {
        std::print("a(g{}) = {}\n", p, poly_fmt(quotients_ordered[p], compare_lex));
    }

    // 3. Graded lex
    auto [quotients_graded, remainder_graded] = poly_reduce(poly, G, compare_graded_lex);
    std::print("Remainder (graded lex): {}\n", poly_fmt(remainder_graded, compare_lex));
    for (size_t p = 0; p < quotients_graded.size(); ++p) {
        std::print("a(g{}) = {}\n", p, poly_fmt(quotients_graded[p], compare_lex));
    }
}