#include <stdio.h>
#include "libjpp.h"

int main(void) {
    uint64_t a = 29, b = 10, c = gcd(a,b);
    diophantine_result64_t result = diophantine(a, b, c);
    if (result.err) {
        printf("No solution for %lu x - %lu y = %lu\n", a, b, c);
    } else {
        printf("Solution for %lu x - %lu y = %lu: x = %lu, y = %lu\n", a, b, c, result.x, result.y);
    }
    return 0;
}