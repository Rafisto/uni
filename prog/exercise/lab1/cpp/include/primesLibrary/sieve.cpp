#include <vector>
#include <stdexcept>

#include "primes_library.h"

std::vector<int> PrimesLib::Sieve(size_t n)
{
    if (n < 2)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "n must be greater than 1. Got " + std::to_string(n) + " instead.");
        return {};
    }

    std::vector<bool> prime(n + 1, true);
    std::vector<int> primes;

    for (long p = 2; p * p <= (long)n; p++)
    {
        if (prime[p])
        {
            for (long i = p * p; i <= (long)n; i += p)
            {
                prime[i] = false;
            }
        }
    }

    for (int p = 2; p <= n; p++)
    {
        if (prime[p])
        {
            primes.push_back(p);
        }
    }

    return primes;
};
