#include <figure.hpp>
#include <cmath>

#ifndef CPP_CIRCLE_H
#define CPP_CIRCLE_H

/*
 * Class Circle
 * Represents a circle
 *
 * @method area() - returns the area of the circle
 * @method perimeter() - returns the perimeter of the circle
 * @method name() - returns the name of the circle
 *
 * @param radius - the radius of the circle
 *
 */
class Circle : public Figure
{
private:
    double radius;

public:
    Circle(double radius) noexcept(false);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
};

#endif // CPP_CIRCLE_H
