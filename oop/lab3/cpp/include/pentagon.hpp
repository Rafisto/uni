//
// Created by Rafist0 on 4/1/2024.
//

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
    Pentagon(double s)
    {
        if (s <= 0)
        {
            throw std::invalid_argument("Side length must be greater than 0.");
        }
        this->side = s;
    }

    double area() const override
    {
        return 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * this->side * this->side;
    }

    double perimeter() const override
    {
        return 5 * this->side;
    }

    const char *name() const override
    {
        return "Pentagon";
    }
};

#endif // CPP_PENTAGON_H
