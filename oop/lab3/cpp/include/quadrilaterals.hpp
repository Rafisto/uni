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
    Square(double s) noexcept(false);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
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
    Rectangle(double l, double w) noexcept(false);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
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
    Rhombus(double s, double a) noexcept(false);
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const char *name() const noexcept(true) override;
};

#endif // CPP_QUADRILATERALS_H
