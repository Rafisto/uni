#include <stdexcept>
#include <cmath>

#include "quadrilaterals.hpp"

Square::Square(double s) noexcept(false)
{
    if (s <= 0)
    {
        throw std::invalid_argument("Side length must be greater than 0.");
    }
    side = s;
}

double Square::area() const noexcept(true)
{
    return side * side;
}

double Square::perimeter() const noexcept(true)
{
    return 4 * side;
}

const char *Square::name() const noexcept(true)
{
    return "Square";
}

Rectangle::Rectangle(double l, double w) noexcept(false)
{
    if (l <= 0 || w <= 0)
    {
        throw std::invalid_argument("Length and width must be greater than 0.");
    }
    length = l;
    width = w;
}

double Rectangle::area() const noexcept(true)
{
    return length * width;
}

double Rectangle::perimeter() const noexcept(true)
{
    return 2 * (length + width);
}

const char *Rectangle::name() const noexcept(true)
{
    return "Rectangle";
}

Rhombus::Rhombus(double s, double a) noexcept(false)
{
    if (s <= 0 || a <= 0)
    {
        throw std::invalid_argument("Side length and angle must be greater than 0.");
    }
    side = s;
    angle = a;
}

double Rhombus::area() const noexcept(true)
{
    return side * side * sin(angle * M_PI / 180);
}

double Rhombus::perimeter() const noexcept(true)
{
    return 4 * side;
}

const char *Rhombus::name() const noexcept(true)
{
    return "Rhombus";
}
