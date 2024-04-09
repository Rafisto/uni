#include <cassert>
#include <string.h>
#include <cmath>

#include <stdio.h>

#include <quadrilaterals.hpp>

#define TOLERANCE 1e-6

void testSquare() noexcept(true);
void testRectangle() noexcept(true);
void testRhombus() noexcept(true);
void testQuadrilaterals() noexcept(true);

void testSquare() noexcept(true) {
    Square square(5); 
    assert(fabs(square.area() - 25) < TOLERANCE);
    assert(fabs(square.perimeter() - 20) < TOLERANCE);
    assert(strcmp(square.name(), "Square") == 0);
}

void testRectangle() noexcept(true) {
    Rectangle rectangle(4, 6);
    assert(fabs(rectangle.area() - 24) < TOLERANCE);
    assert(fabs(rectangle.perimeter() - 20) < TOLERANCE);
    assert(strcmp(rectangle.name(), "Rectangle") == 0);
}

void testRhombus() noexcept(true) {
    Rhombus rhombus(5, 60);
    assert(fabs(rhombus.area() - 21.650635) < TOLERANCE);
    assert(fabs(rhombus.perimeter() - 20) < TOLERANCE);
    assert(strcmp(rhombus.name(), "Rhombus") == 0);
}

void testQuadrilaterals() noexcept(true) {
    testSquare();
    testRectangle();
    testRhombus();
}