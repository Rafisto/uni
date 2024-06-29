#include <stdexcept>

#include "circle.hpp"

Circle::Circle(double radius) noexcept(false)
{
    if (radius <= 0)
    {
        throw std::invalid_argument("Radius must be greater than 0.");
    }
    this->radius = radius;
}

double Circle::area() const noexcept(true)
{
    return M_PI * this->radius * this->radius;
}

double Circle::perimeter() const noexcept(true)
{
    return 2 * M_PI * this->radius;
}

const char *Circle::name() const noexcept(true)
{
    return "Circle";
}
