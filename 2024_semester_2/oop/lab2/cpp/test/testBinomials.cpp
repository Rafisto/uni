#include <cmath>
#include <cassert>

#include <binomials.hpp>

void testBinomials() noexcept(true);
static void testBinomialsNormalCase() noexcept(true);
static void testBinomialsExceptions(const int n) noexcept(true);

void testBinomialsNormalCase() noexcept(true)
{
    assert(Binomials::generateRow(0) == (std::vector<int>{1}));
    assert(Binomials::generateRow(1) == (std::vector<int>{1, 1}));
    assert(Binomials::generateRow(2) == (std::vector<int>{1, 2, 1}));
    assert(Binomials::generateRow(3) == (std::vector<int>{1, 3, 3, 1}));
    assert(Binomials::generateRow(4) == (std::vector<int>{1, 4, 6, 4, 1}));
    assert(Binomials::generateRow(5) == (std::vector<int>{1, 5, 10, 10, 5, 1}));
    assert(Binomials::generateRow(6) == (std::vector<int>{1, 6, 15, 20, 15, 6, 1}));
    assert(Binomials::generateRow(7) == (std::vector<int>{1, 7, 21, 35, 35, 21, 7, 1}));
    assert(Binomials::generateRow(8) == (std::vector<int>{1, 8, 28, 56, 70, 56, 28, 8, 1}));
    assert(Binomials::generateRow(9) == (std::vector<int>{1, 9, 36, 84, 126, 126, 84, 36, 9, 1}));
    assert(Binomials::generateRow(10) == (std::vector<int>{1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1}));
}

void testBinomialsExceptions(const int n) noexcept(true)
{
    try
    {
        const auto row = Binomials::generateRow(n);
        (void)row;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testBinomials() noexcept(true)
{
    testBinomialsNormalCase();

    testBinomialsExceptions(-1);
    testBinomialsExceptions(-2137);
    testBinomialsExceptions(420);
    testBinomialsExceptions(35);
    testBinomialsExceptions(100);
}