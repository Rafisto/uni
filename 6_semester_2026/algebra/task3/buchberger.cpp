#include <print>
#include "buchberger.hpp"

constexpr int64_t v[] = {2, 7, 9, 7, 6, 2};

constexpr int64_t a = v[0];
constexpr int64_t b = v[1];
constexpr int64_t c = v[2];
constexpr int64_t d = v[3];
constexpr int64_t e = v[4];
constexpr int64_t f = v[5];

int main()
{
    // c)
    std::print("C)\n");

    const poly_t M = {
        // powers of {x,y,z} : coeff
        {{2, 0, 0}, 1},  // x^2
        {{0, 2, 0}, 1},  // y^2
        {{0, 0, 2}, -1}, // -z^2
    };

    const std::vector<poly_t> Ps = {
        {{{0, 0, 1}, (c + 1)}},                                               // (c+1)z
        {{{0, 0, 1}, 1}, {{0, 0, 0}, d + 1}},                                 // z + d + 1
        {{{1, 0, 0}, 1}, {{0, 0, 1}, 1}, {{0, 0, 0}, e - 1}},                 // x + z - e - 1
        {{{1, 0, 0}, 1}, {{0, 1, 0}, 1}, {{0, 0, 1}, 1}, {{0, 0, 0}, f + 1}}, // x + y + z - f + 1
        {{{0, 1, 0}, 1}, {{0, 0, 1}, a}, {{0, 0, 0}, a}},                     // y/a + z + 1 (= y + az + a)
    };

    std::vector<size_t> pi{2, 0,1}; 
    g_pi = pi;

    size_t i = 0;
    for (poly_t P : Ps)
    {
        i++;
        std::print("{}... Grobner basis von {} und {}\n", i, poly_fmt(M, compare_lex), poly_fmt(P, compare_lex));
        auto G = buchberger({M, P}, compare_ordered_wrapper);
        std::print("Computed Groebner basis:\n");
        for (const auto &g : G)
        {
            std::print("{}\n", poly_fmt(g, compare_lex));
        }
    }

    // d)
    std::print("D)\n");

    const poly_t D1 = {
        // (x^2+y^2-ax)^2 = z^2(x^2+y^2)
        // is
        // + a^2 x^2
        // - 2 a x^3
        // - 2 a x y^2
        // + x^4
        // + 2 x^2 y^2
        // + y^4
        // - x^2 z^2
        // - y^2 z^2
        {{2, 0, 0}, a * a},
        {{3, 0, 0}, -2 * a},
        {{1, 2, 0}, -2 * a},
        {{4, 0, 0}, 1},
        {{2, 2, 0}, 2},
        {{0, 4, 0}, 1},
        {{2, 0, 2}, -1},
        {{0, 2, 2}, -1}};

    const poly_t D2 = {
        // x + 2y + 3z = 0
        {{1, 0, 0}, 1},
        {{0, 1, 0}, 2},
        {{0, 0, 1}, 3}};

    std::print("Grobner basis von {} und {}\n", poly_fmt(D1, compare_lex), poly_fmt(D2, compare_lex));
    auto G = buchberger({D1, D2}, compare_lex);
    std::print("Computed Groebner basis:\n");
    for (const auto &g : G)
    {
        std::print("{}\n", poly_fmt(g, compare_lex));
    }

    // echo "(y^4) + 4.80(y^3)(z) + 1.60(y^3) + 9.160(y^2)(z^2) + 6.240(y^2)(z) + 0.640(y^2) + 8.160(y)(z^3) + 8.640(y)(z^2) + 1.920(y)(z) + 2.880(z^4) + 4.320(z^3) + 1.440(z^2)" | sed "s/y/x/g" | sed "s/z/y/g"
    // geogebra input: 
    /*
    (x^4) + 4.80(x^3)(y) + 1.60(x^3) + 9.160(x^2)(y^2) + 6.240(x^2)(y) + 0.640(x^2) + 8.160(x)(y^3) + 8.640(x)(y^2) + 1.920(x)(y) + 2.880(y^4) + 4.320(y^3) + 1.440(y^2) = 0
    */ 

    // geogebra alternate (last from 'd)')
    // (x^2 + y^2 - ax)^2 = a^2(x^2 + y^2) , a = 2 therefore
    /*
    (x^2 + y^2 - 2x)^2 = 4*(x^2 + y^2)
    */

    // e) 
    std::print("E)\n");

        //      x^2 + y^2 - r^2 = 0
        // b r^2 + 4bx^2 - r^2 x = 0

    const poly_t E1 = {
        {{0, 0, 2}, 1}, // 1 * x^2
        {{0, 2, 0}, 1}, // 1 * y^2
        {{2, 0, 0}, -1} // -1 * r^2
    };

    const poly_t E2 = {
        {{0, 0, 2}, 4 * b}, // 4b * x^2
        {{2, 0, 0}, b}, // b * r^2
        {{2, 0, 1}, -1} // -1 * r^2 * x
    };

    std::print("Grobner basis von {} und {}\n", poly_fmt(E1, compare_lex), poly_fmt(E2, compare_lex));
    auto E = buchberger({E1, E2}, compare_lex);
    std::print("Computed Groebner basis:\n");
    for (const auto &e : E)
    {
        std::print("{}\n", poly_fmt(e, compare_lex));
    }

    return 0;
}