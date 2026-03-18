#include <assert.h>
#include "libjpp.h"

int test_gcd(void);
int test_first_prime_div(void);
int test_phi(void);
int test_diophantine(void);

int main(void) {
    test_gcd();
    test_first_prime_div();
    test_phi();
    test_diophantine();
}

int test_gcd() {
    assert(gcd(48, 18) == 6);
    assert(gcd(0, 5) == 5);
    assert(gcd(5, 0) == 5);
    assert(gcd(0, 0) == 0);
    return 0;
}

int test_first_prime_div() {
    assert(first_prime_div(31) == 31);
    assert(first_prime_div(29) == 29);
    assert(first_prime_div(4) == 2);
    return 0;
}

int test_phi() {
    assert(phi(1) == 1);
    assert(phi(2) == 1);
    assert(phi(3) == 2);
    assert(phi(4) == 2);
    assert(phi(5) == 4);
    return 0;
}

int test_diophantine() {
    diophantine_result64_t res = diophantine(15, 10, 5);
    assert(!res.err);
    assert(15 * res.x - 10 * res.y == 5);

    res = diophantine(15, 10, 4);
    assert(res.err);

    return 0;
}