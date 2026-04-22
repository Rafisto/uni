#include <cassert>

#include "diophantine.hpp"
#include "power.hpp"
#include "ring.hpp"
#include "rsa.hpp"

int main() {
  const uint64_t p = 10007;
  const uint64_t q = 10009;
  using R = Ring<p * q>;

  RSA<R> rsa(p, q);
  R message(12345);
  
  assert(rsa.getModulo() == p * q);
  assert(rsa.getPublicKey() < (p - 1) * (q - 1));  
  
  // encryption
  R encrypted = rsa.encrypt(message);
  assert(encrypted == power((uint64_t)message, (uint64_t)rsa.getPublicKey(), p * q));
  assert(rsa.decrypt(rsa.encrypt(message)) == message);
  
  // decryption
  uint64_t d = diophantine(rsa.getPublicKey(), (p - 1) * (q - 1), 1).x;
  assert(power((uint64_t)encrypted, d, p * q) == message);
  assert(power((uint64_t)encrypted, d, p * q) == rsa.decrypt(encrypted));
  assert(power((uint64_t)encrypted, d, p * q) != (message + 1));

  return 0;
}