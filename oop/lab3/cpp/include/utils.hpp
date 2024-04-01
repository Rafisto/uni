//
// Created by Rafist0 on 4/1/2024.
//

#ifndef CPP_FIGUREUTILS_H
#define CPP_FIGUREUTILS_H

#define TOLERANCE 1e-6

#include <algorithm>
#include <cmath>
#include <figure.hpp>
#include <quadrilateral.hpp>

class FigureUtils
{
public:
    FigureUtils() = delete;
    ~FigureUtils() = delete;

    static bool isSquare(double a, double b, double c, double d, double angle)
    {
        if (!isRectangle(a, b, c, d, angle))
            return false;

        double sides[4] = {a, b, c, d};
        std::sort(sides, sides + 4);

        if (fabs(sides[0] - sides[3]) < TOLERANCE)
            return true;
        else
            return false;
    }

    static bool isRhombus(double a, double b, double c, double d)
    {
        double sides[4] = {a, b, c, d};
        std::sort(sides, sides + 4);

        if (fabs(sides[0] - sides[3]) < TOLERANCE)
            return true;
        else
            return false;
    }

    static bool isRectangle(double a, double b, double c, double d, double angle)
    {
        if (fabs(angle - 90) > TOLERANCE)
            return false;

        double sides[4] = {a, b, c, d};
        std::sort(sides, sides + 4);

        if (fabs(sides[0] - sides[1]) < TOLERANCE &&
            fabs(sides[2] - sides[3]) < TOLERANCE &&
            fabs(sides[1] - sides[2]) > TOLERANCE)
            return true;
        else
            return false;
    }

    static void printFigureInfo(const Figure &figure)
    {
        std::cout << "Area of the figure: " << figure.area() << std::endl;
        std::cout << "Perimeter of the figure: " << figure.perimeter() << std::endl;
        std::cout << "Name of the figure: " << figure.name() << std::endl;
    }
};

#endif // CPP_FIGUREUTILS_H
