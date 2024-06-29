#include <cmath>
#include <cassert>
#include <stdexcept>
#include <cstddef>

#include <primeNumbers.hpp>

void testPrimeNumbers() noexcept(true);
static void testPrimeNumbersNormalCase() noexcept(true);
static void testPrimeNumbersExceptions(const int val) noexcept(true);
static void testGetPrimeNumbersException(const int gen, const int val) noexcept(true);

void testPrimeNumbersNormalCase() noexcept(true)
{
    {
        PrimeNumbers p = PrimeNumbers(2);
        assert(p.getPrime(0) == 2);
        assert(p.getCount() == 1);
    }
    {
        PrimeNumbers p = PrimeNumbers(3);
        assert(p.getPrime(0) == 2);
        assert(p.getPrime(1) == 3);
        assert(p.getCount() == 2);
    }
    {
        PrimeNumbers p = PrimeNumbers(420);
        assert(p.getPrime(0) == 2);
        assert(p.getPrime(10) == 31);
        assert(p.getPrime(80) == 419);
        assert(p.getCount() == 81);
    }
    {
        PrimeNumbers p = PrimeNumbers(2137);
        assert(p.getPrime(0) == 2);
        assert(p.getPrime(10) == 31);
        assert(p.getPrime(100) == 547);
        assert(p.getPrime(300) == 1993);
        assert(p.getCount() == 322);
    }
}

void testPrimeNumbersExceptions(const int val) noexcept(true)
{
    try
    {
        const auto primes = PrimeNumbers(val);
        (void)primes;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testGetPrimeNumbersException(const int gen, const int val) noexcept(true)
{
    try
    {
        auto primes = PrimeNumbers(gen);
        primes.getPrime(val);
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testPrimeNumbers() noexcept(true)
{
    testPrimeNumbersNormalCase();

    testPrimeNumbersExceptions(0);
    testPrimeNumbersExceptions(1);
    testPrimeNumbersExceptions(-1);
    testPrimeNumbersExceptions(-420);
    testPrimeNumbersExceptions(-2137);

    testGetPrimeNumbersException(2, -1);
    testGetPrimeNumbersException(1, -42);
    testGetPrimeNumbersException(2137, -420);
}