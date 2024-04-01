//
// Created by Rafist0 on 4/1/2024.
//

#ifndef CPP_QUADRILATERALS_H
#define CPP_QUADRILATERALS_H

#include <quadrilateral.hpp>

/*
 * Class Square
 * Represents a square
 *
 * @method area() - returns the area of the square
 * @method perimeter() - returns the perimeter of the square
 * @method name() - returns the name of the square
 */
class Square : public Quadrilateral
{
private:
    double side;

public:
    Square(double s) : side(s) {}

    double area() const override
    {
        return side * side;
    }

    double perimeter() const override
    {
        return 4 * side;
    }

    const char *name() const override
    {
        return "Square";
    }
};

/*
 * Class Rectangle
 * Represents a rectangle
 *
 * @method area() - returns the area of the rectangle
 * @method perimeter() - returns the perimeter of the rectangle
 * @method name() - returns the name of the rectangle
 */
class Rectangle : public Quadrilateral
{
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const override
    {
        return length * width;
    }

    double perimeter() const override
    {
        return 2 * (length + width);
    }

    const char *name() const override
    {
        return "Rectangle";
    }
};

/*
 * Class Rhombus
 * Represents a rhombus
 *
 * @method area() - returns the area of the rhombus
 * @method perimeter() - returns the perimeter of the rhombus
 * @method name() - returns the name of the rhombus
 */
class Rhombus : public Quadrilateral
{
private:
    double side;
    double angle;

public:
    Rhombus(double s, double a) : side(s), angle(a) {}

    double area() const override
    {
        return side * side * sin(angle);
    }

    double perimeter() const override
    {
        return 4 * side;
    }

    const char *name() const override
    {
        return "Rhombus";
    }
};

#endif // CPP_QUADRILATERALS_H
