#include <stdexcept>

#include "pentagon.hpp"

Pentagon::Pentagon(double s)
{
    if (s <= 0)
    {
        throw std::invalid_argument("Side length must be greater than 0.");
    }
    this->side = s;
}

double Pentagon::area() const noexcept(true)
{
    return 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * this->side * this->side;
}

double Pentagon::perimeter() const noexcept(true)
{
    return 5 * this->side;
}

const char *Pentagon::name() const noexcept(true)
{
    return "Pentagon";
}
