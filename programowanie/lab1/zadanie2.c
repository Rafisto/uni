#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("Input coefficients (a b c) of the quadratic equation ax^2 + bx + c = 0. Separate them with spaces.\n");

    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                printf("Infinite number of roots.\n");
            }
            else
            {
                printf("No real roots.\n");
            }
        }
        else
        {
            double root = -c / b;
            printf("One real root: %lf\n", root);
        }
    }
    else
    {
        double delta = b * b - 4 * a * c;

        if (delta < 0)
        {
            printf("No real roots.\n");
        }
        else if (delta == 0)
        {
            double root = -b / (2 * a);
            printf("One real root: %lf\n", root);
        }
        else
        {
            double root1 = (-b - sqrtf(delta)) / (2 * a);
            double root2 = (-b + sqrtf(delta)) / (2 * a);
            printf("Two real roots: %lf and %lf\n", root1, root2);
        }
    }

    return 0;
}
