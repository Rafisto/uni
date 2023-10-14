#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("Input coefficients (a b c) of the quadratic equation ax^2 + bx + c = 0. Separate them with spaces.\n");

    float a, b, c;
    scanf("%f %f %f", &a, &b, &c);

    float delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        printf("No real roots.\n");
    }
    else if (delta == 0)
    {
        float root = -b / (2 * a);
        printf("One real root: %f\n", root);
    }
    else
    {
        float root1 = (-b - sqrtf(delta)) / (2 * a);
        float root2 = (-b + sqrtf(delta)) / (2 * a);
        printf("Two real roots: %f and %f\n", root1, root2);
    }

    return 0;
}
