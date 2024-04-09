#ifndef CPP_FIGURE_H
#define CPP_FIGURE_H

/*
 * Abstract class Figure
 * Represents a geometric figure
 *
 * @method area() - returns the area of the figure
 * @method perimeter() - returns the perimeter of the figure
 * @method name() - returns the name of the figure
 */
class Figure
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual const char *name() const = 0;
    virtual ~Figure() {}
};

#endif // CPP_FIGURE_H
