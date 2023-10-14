#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("Input 3 coefficients of ax^2+bx+c=0. Separate them with spaces.\n");
    float a, b, c;
    scanf("%f %f %f", &a, &b, &c);
    float delta = b * b - 4 * a * c;
    if (delta < 0)
    {
        printf("No real roots\n");
    }
    else if (delta == 0)
    {
        printf("One real root: %f\n", (float)-b / (2 * a));
    }
    else
    {
        printf("Two real roots: %f and %f\n", (float)(-b - sqrtf(delta)) / (2 * a), (float)(-b + sqrtf(delta)) / (2 * a));
    }
    return 0;
}