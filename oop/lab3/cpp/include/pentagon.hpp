#include <stdexcept>
#include <cmath>

#include <figure.hpp>

#ifndef CPP_PENTAGON_H
#define CPP_PENTAGON_H

/*
 * Class Pentagon
 * Represents a pentagon
 *
 * @method area() - returns the area of the pentagon
 * @method perimeter() - returns the perimeter of the pentagon
 * @method name() - returns the name of the pentagon
 *
 * @param size - the size of the pentagon
 */
class Pentagon : public Figure
{
private:
    double side;

public:
    Pentagon(double s);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
};

#endif // CPP_PENTAGON_H
