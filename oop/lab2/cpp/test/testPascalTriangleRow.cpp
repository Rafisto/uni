#include <cmath>
#include <cassert>

#include <pascalTriangleRow.hpp>

void testPascalTriangleRow() noexcept(true);
static void testPascalTriangleRowNormalCase() noexcept(true);
static void testPascalTriangleRowExceptions(const int val) noexcept(true);

void testPascalTriangleRowNormalCase() noexcept(true)
{
    {
        PascalTriangleRow p = PascalTriangleRow(0);
        assert(p.getCoefficient(0) == 1);
    }
    {
        PascalTriangleRow p = PascalTriangleRow(1);
        assert(p.getCoefficient(0) == 1);
        assert(p.getCoefficient(1) == 1);
    }
    {
        PascalTriangleRow p = PascalTriangleRow(2);
        assert(p.getCoefficient(0) == 1);
        assert(p.getCoefficient(1) == 2);
        assert(p.getCoefficient(2) == 1);
    }
    {
        PascalTriangleRow p = PascalTriangleRow(3);
        assert(p.getCoefficient(0) == 1);
        assert(p.getCoefficient(1) == 3);
        assert(p.getCoefficient(2) == 3);
        assert(p.getCoefficient(3) == 1);
    }
    {
        PascalTriangleRow p = PascalTriangleRow(4);
        assert(p.getCoefficient(0) == 1);
        assert(p.getCoefficient(1) == 4);
        assert(p.getCoefficient(2) == 6);
        assert(p.getCoefficient(3) == 4);
        assert(p.getCoefficient(4) == 1);
    }
    {
        PascalTriangleRow p = PascalTriangleRow(20);
        assert(p.getCoefficient(0) == 1);
        assert(p.getCoefficient(1) == 20);
        assert(p.getCoefficient(2) == 190);
        assert(p.getCoefficient(3) == 1140);
    }
}

void testPascalTriangleRowExceptions(const int val) noexcept(true)
{
    try
    {
        const auto row = PascalTriangleRow(val);
        (void)row;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testPascalTriangleRow() noexcept(true)
{
    testPascalTriangleRowNormalCase();

    testPascalTriangleRowExceptions(-1);
    testPascalTriangleRowExceptions(-20);
}
