#include <cassert>
#include <cmath>
#include <stdexcept>

#include "circle.hpp"

#define TOLERANCE 10e-6

void testCircle() noexcept(true);
static void testCircleNormalCase() noexcept(true);
static void testCircleExceptions() noexcept(true);

void testCircleNormalCase() noexcept(true)
{
    {
        Circle circle(1);
        assert(fabs(circle.area() - M_PI) < TOLERANCE);
        assert(fabs(circle.perimeter() - (2 * M_PI)) < TOLERANCE);
    }

    {
        Circle circle(5);
        assert(fabs(circle.area() - (M_PI * 25)) < TOLERANCE);
        assert(fabs(circle.perimeter() - (2 * M_PI * 5)) < TOLERANCE);
    }

    {
        Circle circle(10);
        assert(fabs(circle.area() - (M_PI * 100)) < TOLERANCE);
        assert(fabs(circle.perimeter() - (2 * M_PI * 10)) < TOLERANCE);
    }
}

void testCircleExceptions() noexcept(true)
{
    try
    {
        Circle circle(-1);
        (void)circle;
        assert(false && "Exception should be raised for negative radius");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testCircle() noexcept(true)
{
    testCircleNormalCase();
    testCircleExceptions();
}