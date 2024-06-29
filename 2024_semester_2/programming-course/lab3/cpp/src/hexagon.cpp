#include <stdexcept>

#include "hexagon.hpp"

Hexagon::Hexagon(double s) noexcept(false)
{
    if (s <= 0)
    {
        throw std::invalid_argument("Side length must be greater than 0.");
    }
    this->side = s;
}

double Hexagon::area() const noexcept(true)
{
    return 3 * sqrt(3) * this->side * this->side / 2;
}

double Hexagon::perimeter() const noexcept(true)
{
    return 6 * this->side;
}

const char *Hexagon::name() const noexcept(true)
{
    return "Hexagon";
}