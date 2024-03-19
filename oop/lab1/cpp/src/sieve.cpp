#include <sieve.hpp>

#include <vector>
#include <string>

std::vector<int> Sieve::Primes(size_t n) noexcept(false)
{
    if (n < 2)
    {
        throw std::invalid_argument("parameter n should be >= 2, got " + std::to_string(n));
    }

    std::vector<int> primes;
    std::vector<bool> isPrime(n + 1, true);

    for (size_t i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(static_cast<int>(i));
            for (size_t j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    return primes;
}