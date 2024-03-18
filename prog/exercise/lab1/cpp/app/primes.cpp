#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

#include "primes_library/primes_library.h"

#include "headers.h"

PrimeNumbers::PrimeNumbers(int n)
{
    if (n < 2)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Invalid argument: " + std::to_string(n));
    }

    try
    {
        this->primes = PrimesLib::Sieve(static_cast<size_t>(n));
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Failed to create Prime Numbers object: " + e.what());
    }
    catch (const std::out_of_range &e)
    {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Failed to create Prime Numbers object: " + e.what());
    }
}

int PrimeNumbers::getPrime(int index)
{
    if (index < 0)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "index must be greater or equal to 0. Got " + std::to_string(index) + " instead.");
    }

    if (static_cast<size_t>(index) >= primes.size())
    {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "range exceeded. Index must be less than or equal to " + std::to_string(primes.size() - 1) + ". Got " + std::to_string(index) + " instead.");;
    }

    return primes[static_cast<size_t>(index)];
}
