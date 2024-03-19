#include <stdexcept>
#include <string>

#include <primeNumbers.hpp>
#include <sieve.hpp>

PrimeNumbers::PrimeNumbers(const int n) noexcept(false)
{
    if (n < 2)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Invalid argument: " + std::to_string(n));
    }
    this->primes = Sieve::Primes(static_cast<size_t>(n));
}

int PrimeNumbers::getPrime(int m) noexcept(false)
{
    if (m < 0)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "index must be greater or equal to 0. Got " + std::to_string(m) + " instead.");
    }
    if (static_cast<size_t>(m) >= this->primes.size())
    {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "range exceeded. Index must be less than or equal to " + std::to_string(this->primes.size() - 1) + ". Got " + std::to_string(m) + " instead.");
    }

    return this->primes[static_cast<size_t>(m)];
}

std::size_t PrimeNumbers::getCount() const noexcept
{
    return this->primes.size();
}