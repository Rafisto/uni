#include <cassert>
#include <string.h>

#include <pentagon.hpp>

#define TOLERANCE 10e-6

void testPentagon() noexcept(true);
static void testPentagonNormalCase() noexcept(true);
static void testPentagonExceptions(const int n) noexcept(true);

void testPentagonNormalCase() noexcept(true)
{
    {
        Pentagon pentagon = Pentagon(1);
        assert(fabs(pentagon.area() - 1.720477) < TOLERANCE);
        assert(fabs(pentagon.perimeter() - 5) < TOLERANCE);
        assert(strcmp(pentagon.name(), "Pentagon") == 0);
    }
    {
        Pentagon pentagon = Pentagon(6);
        assert(fabs(pentagon.area() - 61.937186) < TOLERANCE);
        assert(fabs(pentagon.perimeter() - 30) < TOLERANCE);
        assert(strcmp(pentagon.name(), "Pentagon") == 0);
    }
    {
        Pentagon pentagon = Pentagon(10);
        assert(fabs(pentagon.area() - 172.047740) < TOLERANCE);
        assert(fabs(pentagon.perimeter() - 50) < TOLERANCE);
        assert(strcmp(pentagon.name(), "Pentagon") == 0);
    }
    {
        Pentagon pentagon = Pentagon(100);
        assert(fabs(pentagon.area() - 17204.774006) < TOLERANCE);
        assert(fabs(pentagon.perimeter() - 500) < TOLERANCE);
        assert(strcmp(pentagon.name(), "Pentagon") == 0);
    }
}

void testPentagonExceptions(const int n) noexcept(true)
{
    try
    {
        Pentagon pentagon = Pentagon(n);
        (void)pentagon;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testPentagon() noexcept(true)
{
    testPentagonNormalCase();

    testPentagonExceptions(-1);
    testPentagonExceptions(-2137);
    testPentagonExceptions(-420);
    testPentagonExceptions(-1000000);
}