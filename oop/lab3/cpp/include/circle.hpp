//
// Created by Rafist0 on 4/1/2024.
//

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
    Circle(double radius) noexcept(false)
    {
        if (radius <= 0)
        {
            throw std::invalid_argument("Radius must be greater than 0.");
        }
        this->radius = radius;
    }

    double area() const override
    {
        return M_PI * this->radius * this->radius;
    }

    double perimeter() const override
    {
        return 2 * M_PI * this->radius;
    }

    const char *name() const override
    {
        return "Circle";
    }
};

#endif // CPP_CIRCLE_H