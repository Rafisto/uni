#include <stdio.h>

int main(void)
{
    double x = 1.0;
    double y = 2.0;
    printf("%lf| %lf\n", x, y);
    y = 0.5 * (x + y);
    printf("%lf| %lf\n", x, y);
    x = 2.0 / y;
    printf("%lf| %lf\n", x, y);
    y = 0.5 * (x + y);
    printf("%lf| %lf\n", x, y);
    x = 2.0 / y;
    printf("%lf| %lf\n", x, y);
    y = 0.5 * (x + y);
    printf("%lf| %lf\n", x, y);
    x = 2.0 / y;
    printf("%lf| %lf\n", x, y);
    y = 0.5 * (x + y);
    printf("%lf| %lf\n", x, y);
    x = 2.0 / y;
    printf("%lf| %lf\n", x, y);
    return 0;
}