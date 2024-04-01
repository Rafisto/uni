#include <iostream>

#include <stringConverter.hpp>
#include <utils.hpp>

#include <figure.hpp>
#include <quadrilateral.hpp>

#include <circle.hpp>
#include <pentagon.hpp>
#include <hexagon.hpp>
#include <quadrilaterals.hpp>

int main(const int argc, const char *const argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [o|c|p|s] [additional arguments...]" << std::endl;
        return 1;
    }

    switch (argv[1][0])
    {
    case 'o':
        std::cout << "Option o selected" << std::endl;
        if (argc < 3)
        {
            std::cerr << "Radius not provided." << std::endl;
            return 1;
        }
        try
        {
            const auto radius = StringConverter::stringToVal<double>(std::string(argv[2]));
            Circle circle(radius);
            std::cout << "Area of the figure: " << circle.area() << std::endl;
            std::cout << "Perimeter of the figure: " << circle.perimeter() << std::endl;
            std::cout << "Name of the figure: " << circle.name() << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 'c':
        // Handle case 'c'
        std::cout << "Option c selected" << std::endl;
        if (argc < 7)
        {
            std::cerr << "4 side lengths and angle not provided." << std::endl;
            return 1;
        }
        try
        {
            const auto side1 = StringConverter::stringToVal<double>(std::string(argv[2]));
            const auto side2 = StringConverter::stringToVal<double>(std::string(argv[3]));
            const auto side3 = StringConverter::stringToVal<double>(std::string(argv[4]));
            const auto side4 = StringConverter::stringToVal<double>(std::string(argv[5]));
            const auto angle = StringConverter::stringToVal<double>(std::string(argv[6]));
            if (FigureUtils::isSquare(side1, side2, side3, side4, angle))
            {
                Square square(side1);
                FigureUtils::printFigureInfo(square);
            }
            else if (FigureUtils::isRhombus(side1, side2, side3, side4))
            {
                Rhombus rhombus(side1, angle);
                FigureUtils::printFigureInfo(rhombus);
            }
            else if (FigureUtils::isRectangle(side1, side2, side3, side4, angle))
            {
                Rectangle rectangle(side1, side2);
                FigureUtils::printFigureInfo(rectangle);
            }
            else
            {
                throw std::invalid_argument("Invalid Quadrilateral");
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 'p':
        // Handle case 'p'
        std::cout << "Option p selected" << std::endl;
        if (argc < 3)
        {
            std::cerr << "Side length not provided." << std::endl;
            return 1;
        }
        try
        {
            const auto side_length = StringConverter::stringToVal<double>(std::string(argv[2]));
            Pentagon pentagon(side_length);
            std::cout << "Area of the figure: " << pentagon.area() << std::endl;
            std::cout << "Perimeter of the figure: " << pentagon.perimeter() << std::endl;
            std::cout << "Name of the figure: " << pentagon.name() << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 's':
        // Handle case 's'
        std::cout << "Option s selected" << std::endl;
        if (argc < 3)
        {
            std::cerr << "Side length not provided." << std::endl;
            return 1;
        }
        try
        {
            const auto side_length = StringConverter::stringToVal<double>(std::string(argv[2]));
            Hexagon hexagon(side_length);
            std::cout << "Area of the figure: " << hexagon.area() << std::endl;
            std::cout << "Perimeter of the figure: " << hexagon.perimeter() << std::endl;
            std::cout << "Name of the figure: " << hexagon.name() << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    default:
        // Throw an exception for invalid input
        throw std::invalid_argument("Invalid option");
    }

    return 0;
}