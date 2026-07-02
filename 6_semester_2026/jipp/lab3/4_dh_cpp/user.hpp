#ifndef USER_HPP
#define USER_HPP

#include <stdexcept>

#include "dh.hpp"

template <typename T> class User {
private:
  const DHSetup<T> &setup;
  long long secret;
  T sharedKey;
  bool keySet;

public:
  User(const DHSetup<T> &s) : setup(s), sharedKey(0), keySet(false) {
    secret = T::g();
  }

  T getPublicKey() const { return setup.power(setup.getGenerator(), secret); }

  void setKey(T a) {
    sharedKey = setup.power(a, secret);
    keySet = true;
  }

  T encrypt(T m) const {
    if (!keySet)
      throw std::invalid_argument("key not set");
    return m * sharedKey;
  }

  T decrypt(T c) const {
    if (!keySet)
      throw std::invalid_argument("key not set");
    return c / sharedKey;
  }
};


#endif