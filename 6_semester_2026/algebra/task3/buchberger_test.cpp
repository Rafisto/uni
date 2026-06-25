#include <print>
#include "buchberger.hpp"

int main() {
    std::vector<poly_t> F = {
        // grobnerbasis({x-uv,y-v,z-u^2},{u,v,x,y,z})
        // x - uv
        // y - v
        // z - u^2
        // {u,v,x,y,z}
        {{ {0,0,1,0,0}, 1 }, { {1,1,0,0,0}, -1 }}, // x - uv
        {{ {0,0,0,1,0}, 1 }, { {0,1,0,0,0}, -1 }}, // y - v
        {{ {0,0,0,0,1}, 1 }, { {2,0,0,0,0}, -1 }}  // z - u^2
    };

    auto order = compare_lex;

    auto G = buchberger(F, order);

    std::print("Computed Groebner basis:\n");
    for (const auto& g : G) {
        std::print("{}\n", poly_fmt(g, order));
    }

    // Computed Groebner basis:
    // (v) - (y)
    // (u^2) - (z)
    // (u)(y) - (x)
    // (u)(x) - (y)(z)
    // (x^2) - (y^2)(z)

    return 0;
}