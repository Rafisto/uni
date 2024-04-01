//
// Created by Rafist0 on 4/1/2024.
//

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
    Hexagon(double s) noexcept(false)
    {
        if (s <= 0)
        {
            throw std::invalid_argument("Side length must be greater than 0.");
        }
        this->side = s;
    }

    double area() const override
    {
        return 3 * sqrt(3) * this->side * this->side / 2;
    }

    double perimeter() const override
    {
        return 6 * this->side;
    }

    const char *name() const override
    {
        return "Hexagon";
    }
};

#endif // CPP_HEXAGON_H
