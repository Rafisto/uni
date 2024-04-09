#include "utils.hpp"

bool FigureUtils::isSquare(double a, double b, double c, double d, double angle)
{
    if (fabs(angle - 90) > TOLERANCE)
        return false;

    double sides[4] = {a, b, c, d};
    std::sort(sides, sides + 4);

    return (fabs(sides[0] - sides[3]) < TOLERANCE);
}

bool FigureUtils::isRhombus(double a, double b, double c, double d)
{
    double sides[4] = {a, b, c, d};
    std::sort(sides, sides + 4);

    return (fabs(sides[0] - sides[3]) < TOLERANCE);
}

bool FigureUtils::isRectangle(double a, double b, double c, double d, double angle)
{
    if (fabs(angle - 90) > TOLERANCE)
        return false;

    double sides[4] = {a, b, c, d};
    std::sort(sides, sides + 4);

    return (fabs(sides[0] - sides[1]) < TOLERANCE &&
            fabs(sides[2] - sides[3]) < TOLERANCE &&
            fabs(sides[1] - sides[2]) > TOLERANCE);
}

void FigureUtils::printFigureInfo(const Figure &figure)
{
    std::cout << "Area of the figure: " << figure.area() << std::endl;
    std::cout << "Perimeter of the figure: " << figure.perimeter() << std::endl;
    std::cout << "Name of the figure: " << figure.name() << std::endl;
}
