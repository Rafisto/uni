#include <iostream>

#include "rsa.hpp"

int main(void) {
    constexpr uint64_t p = 10007;
    constexpr uint64_t q = 10009;
    constexpr uint64_t md = (p-1)*(q-1);

    using R = Ring<10007*10009>;
    RSA<R> rsa(p,q);

}