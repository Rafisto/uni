#ifndef PRIME_NUMBERS_H
#define PRIME_NUMBERS_H

#include <vector>
#include <string>

int parseIntArgv(const char *arg);

class PrimeNumbers
{
private:
    std::vector<int> primes;

public:
    explicit PrimeNumbers(int n);
    int getPrime(int index);
};

#endif
