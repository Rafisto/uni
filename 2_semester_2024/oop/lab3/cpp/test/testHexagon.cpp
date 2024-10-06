#include <cassert>
#include <string.h>

#include <hexagon.hpp>

#define TOLERANCE 10e-6

void testHexagon() noexcept(true);
static void testHexagonNormalCase() noexcept(true);
static void testHexagonExceptions(const int n) noexcept(true);

void testHexagonNormalCase() noexcept(true)
{
    {
        Hexagon hex = Hexagon(1);
        assert(hex.area() - 2.5980762 < TOLERANCE);
        assert(hex.perimeter() - 6 < TOLERANCE);
        assert(strcmp(hex.name(), "Hexagon") == 0);
    }

    {
        Hexagon hex = Hexagon(6);
        assert(hex.area() - 93.5307436 < TOLERANCE);
        assert(hex.perimeter() - 36 < TOLERANCE);
        assert(strcmp(hex.name(), "Hexagon") == 0);
    }

    {
        Hexagon hex = Hexagon(10);
        assert(hex.area() - 259.8076211 < TOLERANCE);
        assert(hex.perimeter() - 60 < TOLERANCE);
        assert(strcmp(hex.name(), "Hexagon") == 0);
    }

    {
        Hexagon hex = Hexagon(100);
        assert(hex.area() - 25980.7621135 < TOLERANCE);
        assert(hex.perimeter() - 600 < TOLERANCE);
        assert(strcmp(hex.name(), "Hexagon") == 0);
    }
}

void testHexagonExceptions(const int n) noexcept(true)
{
    try
    {
        Hexagon hex = Hexagon(n);
        (void)hex;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testHexagon() noexcept(true)
{
    testHexagonNormalCase();

    testHexagonExceptions(-1);
    testHexagonExceptions(-2137);
    testHexagonExceptions(-420);
    testHexagonExceptions(-1000000);
}