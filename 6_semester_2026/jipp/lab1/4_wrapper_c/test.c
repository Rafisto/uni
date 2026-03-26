#include <assert.h>
#include <stdio.h>
#include "libjpp.h"

extern int test_gcd(void);
extern int test_first_prime_div(void);
extern int test_phi(void);
extern int test_diophantine(void);

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

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_first_prime_div() {
    assert(first_prime_div(31) == 31);
    assert(first_prime_div(29) == 29);
    assert(first_prime_div(4) == 2);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_phi() {
    assert(phi(1) == 1);
    assert(phi(2) == 1);
    assert(phi(3) == 2);
    assert(phi(4) == 2);
    assert(phi(5) == 4);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_diophantine() {
    diophantine_result64_t res = diophantine(15, 10, 5);
    assert(!res.err);
    assert(15 * res.x - 10 * res.y == 5);

    res = diophantine(29, 10, gcd(29,10));
    assert(!res.err);
    assert(29 * res.x - 10 * res.y == gcd(29,10));

    printf("%s pass\n", __FUNCTION__);
    return 0;
}