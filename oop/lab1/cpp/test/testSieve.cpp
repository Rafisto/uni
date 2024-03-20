#include <sieve.hpp>

#include <cmath>
#include <cassert>

void testSieve() noexcept(true);
static void testSieveNormalCase() noexcept(true);
static void testSieveExceptions(const int val) noexcept(true);

static void testSieveNormalCase() noexcept(true)
{
    assert(Sieve::Primes(2) == (std::vector<int>{2}));
    assert(Sieve::Primes(3) == (std::vector<int>{2, 3}));
    assert(Sieve::Primes(10) == (std::vector<int>{2, 3, 5, 7}));
    assert(Sieve::Primes(100) == (std::vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}));
}

static void testSieveExceptions(const int val) noexcept(true)
{
    try
    {
        const auto primes = Sieve::Primes(val);
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
    catch (const std::out_of_range &e)
    {
        (void)e;
    }
}

void testSieve() noexcept(true)
{
    testSieveNormalCase();

    testSieveExceptions(0);
    testSieveExceptions(1);
    testSieveExceptions(-1);
    testSieveExceptions(-420);
    testSieveExceptions(-2137);
    testSieveExceptions(-1000000);
}