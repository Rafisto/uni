// Zadanie 2, main.c Rafał Włodarczyk

#include <stdio.h>
#include <math.h>
#include "functions.h"

int main(void)
{
    int a = 2, b = 4;
    for (int i = 1; i <= 8; i++)
    {
        double eps = pow(10, -i);
        printf("a = %d, b = %d, eps = %f, result = %f\n", a, b, eps, rozwiazanie(a, b, eps));
    }
}
