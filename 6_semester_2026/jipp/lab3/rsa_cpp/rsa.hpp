#ifndef RSA_HPP
#define RSA_HPP

#include <random>
#include <stdexcept>
#include "diophantine.hpp"
#include "ring.hpp"

template <Ring T>
class RSA {
private:
    uint64_t e;
    uint64_t d;
    uint64_t phi;

    uint64_t power(uint64_t base, uint64_t exp) const {
        Ring<T.modulus()> b(base);
        Ring<T.modulus()> res(1);
        while (exp > 0) {
            if (exp % 2 == 1) res = res * b;
            b = b * b;
            exp /= 2;
        }
        return res; 
    }

public:
    RSA(uint64_t p, uint64_t q) {
        phi = (p - 1) * (q - 1);

        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dist(2, phi - 1);

        do {
            e = dist(gen);
        } while (gcd(e, phi) != 1);

        diophantine_result64_t res = diophantine((uint64_t)e, (uint64_t)phi, 1);
        if (res.err) {
            throw std::runtime_error("Key generation failed");
        }
        d = res.x % phi;
    }

    Ring<T.modulus()> getModulo() const { return T.modulus(); }
    Ring<T.modulus()> getPublicKey() const { return e; }

    Ring<T.modulus()> encrypt(Ring<T.modulus()> m) const {
        return power(m, e);
    }

    Ring<T.modulus()> decrypt(Ring<T.modulus()> s) const {
        return power(s, d);
    }
};

#endif // RSA_HPP