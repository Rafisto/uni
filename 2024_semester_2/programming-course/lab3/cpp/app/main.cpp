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
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " [o|c|p|s] [at least one additional argument...]" << std::endl;
        return 1;
    }

    Figure *figure = nullptr;

    switch (argv[1][0])
    {
    case 'o':
        std::cout << "Option o selected" << std::endl;
        if (argc > 3)
        {
            std::cerr << "Too many arguments" << std::endl;
            return 1;
        }
        try
        {
            const auto radius = StringConverter::stringToVal<double>(std::string(argv[2]));
            figure = new Circle(radius);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 'c':
        std::cout << "Option c selected" << std::endl;
        if (argc < 7)
        {
            std::cerr << "4 side lengths and angle not provided." << std::endl;
            return 1;
        }
        if (argc > 7)
        {
            std::cerr << "Too many arguments" << std::endl;
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
                figure = new Square(side1);
            }
            else if (FigureUtils::isRhombus(side1, side2, side3, side4, angle))
            {
                figure = new Rhombus(side1, angle);
            }
            else if (FigureUtils::isRectangle(side1, side2, side3, side4, angle))
            {
                if (std::fabs(side1 - side2) < 1e-6 && std::fabs(side3 - side4) < 1e-6) {
                    figure = new Rectangle(side1, side3);
                }
                else if ((std::fabs(side1 - side3) < 1e-6 && std::fabs(side2 - side4) < 1e-6) || (std::fabs(side1 - side4) < 1e-6 && std::fabs(side2 - side3) < 1e-6))
                {
                    figure = new Rectangle(side1, side2);
                } 
                else
                {
                    throw std::invalid_argument("Invalid Rectangle: There should be at least 2 pairs of equal side lengths");
                }
            }
            else
            {
                throw std::invalid_argument("Invalid Quadrilateral.");
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 'p':
        std::cout << "Option p selected" << std::endl;
        if (argc > 3)
        {
            std::cerr << "Too many arguments" << std::endl;
            return 1;
        }
        try
        {
            const auto side_length = StringConverter::stringToVal<double>(std::string(argv[2]));
            figure = new Pentagon(side_length);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    case 's':
        std::cout << "Option s selected" << std::endl;
        if (argc > 3)
        {
            std::cerr << "Too many arguments" << std::endl;
            return 1;
        }
        try
        {
            const auto side_length = StringConverter::stringToVal<double>(std::string(argv[2]));
            figure = new Hexagon(side_length);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 1;
        }
        break;
    default:
        std::cerr << "Invalid option [c|o|p|s]" << std::endl;
        return 1;
    }

    FigureUtils::printFigureInfo(*figure);

    delete figure;

    return 0;
}