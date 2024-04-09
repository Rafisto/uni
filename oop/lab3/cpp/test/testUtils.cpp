#include <cassert>
#include <stdexcept>

#include <utils.hpp>

void testUtils() noexcept(true)
{
    assert(FigureUtils::isSquare(10, 10, 10, 10, 90) == true);
    assert(FigureUtils::isSquare(10, 20, 10, 20, 90) == false);
    assert(FigureUtils::isRhombus(10, 10, 10, 10) == true);
    assert(FigureUtils::isRhombus(10, 10, 10, 11) == false);
    assert(FigureUtils::isRectangle(10, 20, 10, 20, 90) == true);
    assert(FigureUtils::isRectangle(10, 10, 10, 10, 90) == false);
}