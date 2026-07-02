#include <iostream>
#include <cassert>

#include "dh.hpp"
#include "ring.hpp"
#include "user.hpp"

int main() {
    constexpr uint64_t n = 1234567891;
    using R = Ring<n>;

    DHSetup<R> dh;
    User<R> alice(dh);
    User<R> bob(dh);
    R pubA = alice.getPublicKey();
    R pubB = bob.getPublicKey();
    alice.setKey(pubB);
    bob.setKey(pubA);

    R message(12345);
    
    R encrypted = alice.encrypt(message);
    R decrypted = bob.decrypt(encrypted);
    assert(message == decrypted);

    R message2(54321);

    R encrypted2 = alice.encrypt(message2);
    R decrypted2 = bob.decrypt(encrypted2);
    assert(message2 == decrypted2);
    
    std::cout << "DH works" << std::endl;

    return 0;
}