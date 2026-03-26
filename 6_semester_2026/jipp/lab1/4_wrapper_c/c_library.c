#include <assert.h>

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
