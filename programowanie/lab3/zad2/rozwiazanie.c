// Zadanie 2, rozwiazanie.c Rafał Włodarczyk

#include "functions.h"
#include <stdio.h>

double rozwiazanie(double a, double b, double eps)
{
    double m = (a + b) / 2;
    while ((b - a) > eps)
    {
        if (f(m) * f(a) > 0)
        {
            a = m;
        }
        else
        {
            b = m;
        }
        m = (a + b) / 2;
    }
    return m;
}
