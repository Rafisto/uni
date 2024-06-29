//
// Created by Rafist0 on 4/1/2024.
//
#ifndef CPP_QUADRILATERAL_H
#define CPP_QUADRILATERAL_H

#include <stdexcept>

#include <figure.hpp>

/*
 * Abstract class Quadrilateral
 * Represents a quadrilateral
 *
 * @method area() - returns the area of the quadrilateral
 * @method perimeter() - returns the perimeter of the quadrilateral
 * @method name() - returns the name of the quadrilateral
 */
class Quadrilateral : public Figure
{
public:
    virtual double area() const override = 0;      // Pure virtual function
    virtual double perimeter() const override = 0; // Pure virtual function
    virtual const char *name() const override = 0; // Pure virtual function

    virtual ~Quadrilateral() override {} // Virtual destructor
};

#endif // CPP_QUADRILATERAL_H