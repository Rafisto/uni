#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("Input coefficients (a b c) of the quadratic equation ax^2 + bx + c = 0. Separate them with spaces.\n");

    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    double delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        printf("No real roots.\n");
    }
    else if (delta == 0)
    {
        double root = -b / (2 * a);
        printf("One real root: %f\n", root);
    }
    else
    {
        double root1 = (-b - sqrtf(delta)) / (2 * a);
        double root2 = (-b + sqrtf(delta)) / (2 * a);
        printf("Two real roots: %f and %f\n", root1, root2);
    }

    return 0;
}
