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
    // zero case
    assert(gcd(0,0) == 0);

    // base
    assert(gcd(48, 18) == 6);
    assert(gcd(101, 103) == 1);

    // one is a zero
    assert(gcd(0, 5) == 5);
    assert(gcd(5, 0) == 5);
    assert(gcd(0, 0) == 0);

    // max value
    uint64_t max_val = 0xFFFFFFFFFFFFFFFFULL; 
    assert(gcd(max_val, max_val) == max_val);
    assert(gcd(max_val, 1) == 1);

    // large co-prime numbers
    assert(gcd(7540113804746346429ULL, 4660046610375530309ULL) == 1);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_first_prime_div() {
    // zero case
    assert(first_prime_div(0) == 0);

    // base case
    assert(first_prime_div(31) == 31);
    assert(first_prime_div(29) == 29);
    assert(first_prime_div(4) == 2);

    // large primes
    assert(first_prime_div(104729) == 104729);

    // square factors
    assert(first_prime_div(121) == 11);
    assert(first_prime_div(961) == 31);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_phi() {
    // zero case
    assert(phi(0) == 0);

    // base case
    assert(phi(1) == 1);
    assert(phi(2) == 1);
    assert(phi(3) == 2);
    assert(phi(9) == 6);
    assert(phi(10) == 4);

    // larger composites
    assert(phi(100) == 40);
    assert(phi(1000) == 400);

    // co-prime phi(pq) = phi(p) * phi(q) = (p-1)(q-1)
    assert(phi(37) * phi(39) == phi(37 * 39)); 
    assert(phi(101) * phi(103) == 100 * 102);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}

int test_diophantine() {
    // ax - by = c
    diophantine_result64_t res;
    
    // 15x - 10y = 5
    res = diophantine(15, 10, 5);
    assert(!res.err);
    assert(15 * res.x - 10 * res.y == 5);

    // 29x - 10y = gcd(29,10)
    res = diophantine(29, 10, gcd(29,10));
    assert(!res.err);
    assert(29 * res.x - 10 * res.y == gcd(29,10));

    // error case
    res = diophantine(29, 10, gcd(29,10) + 1);
    assert(res.err);

    // a is zero
    res = diophantine(0, 10, 10);
    assert(res.err);

    // b is zero
    res = diophantine(10, 0, 10);
    assert(!res.err);
    assert(res.x == 1);

    // c is zero
    res = diophantine(10, 10, 0);
    assert(res.err);
    assert(10 * res.x - 10 * res.y == 0);

    printf("%s pass\n", __FUNCTION__);
    return 0;
}