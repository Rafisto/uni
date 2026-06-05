#include <print>
#include "polyreduce.hpp"

int main() {
    poly_t poly{
        {{2, 8, 0}, 1},
        {{0, 2, 2}, 1},
        {{1, 0, 0}, 1}
    };

    std::print("Formatted polynomial: {}\n", poly_fmt(poly, compare_graded_lex));

    poly_t g1 = {{{2, 1, 0}, 1}, {{0, 0, 1}, -1}};
    poly_t g2 = {{{1, 0, 0}, -1}, {{0, 2, 1}, 1}};
    poly_t g3 = {{{2, 0, 0}, -1}, {{0, 2, 2}, 1}};

    std::print("g1: {}\n", poly_fmt(g1, compare_lex));
    std::print("g2: {}\n", poly_fmt(g2, compare_lex));
    std::print("g3: {}\n", poly_fmt(g3, compare_lex));

    std::vector<poly_t> G{g1, g2, g3};

    // 1. Lex order
    auto [quotients, remainder] = poly_reduce(poly, G, compare_lex);
    std::print("Remainder (lex): {}\n", poly_fmt(remainder, compare_lex));

    // 2. Ordered lex
    std::vector<size_t> pi{2, 0, 1}; 
    g_pi = pi;
    auto [quotients_ordered, remainder_ordered] = poly_reduce(poly, G, compare_ordered_wrapper);
    std::print("Remainder (ordered lex): {}\n", poly_fmt(remainder_ordered, compare_lex));

    // 3. Graded lex
    auto [quotients_graded, remainder_graded] = poly_reduce(poly, G, compare_graded_lex);
    std::print("Remainder (graded lex): {}\n", poly_fmt(remainder_graded, compare_lex));
}