//
// Created by Rafist0 on 4/1/2024.
//

#ifndef CPP_FIGUREUTILS_H
#define CPP_FIGUREUTILS_H

#define TOLERANCE 1e-6

#include <algorithm>
#include <cmath>
#include <iostream>

#include "figure.hpp"

class FigureUtils {
public:
    FigureUtils() = delete;
    ~FigureUtils() = delete;

    static bool isSquare(double a, double b, double c, double d, double angle);
    static bool isRhombus(double a, double b, double c, double d);
    static bool isRectangle(double a, double b, double c, double d, double angle);
    static void printFigureInfo(const Figure &figure);
};

#endif //CPP_FIGUREUTILS_H
