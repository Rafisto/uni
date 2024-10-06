#include <stdexcept>
#include <cmath>

#include <figure.hpp>

#ifndef CPP_HEXAGON_H
#define CPP_HEXAGON_H

/*
 * Class Hexagon
 * Represents a hexagon
 *
 * @method area() - returns the area of the hexagon
 * @method perimeter() - returns the perimeter of the hexagon
 * @method name() - returns the name of the hexagon
 *
 * @param size - the size of the hexagon
 */
class Hexagon : public Figure
{
private:
    double side;

public:
    Hexagon(double s) noexcept(false);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
};

#endif // CPP_HEXAGON_H
