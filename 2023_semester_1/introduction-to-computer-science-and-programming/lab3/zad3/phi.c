// Zadanie 3, phi.c Rafał Włodarczyk

#include "functions.h"

int phi(long int n)
{
    int phi = 0;
    for (long int i = 1; i <= n; i++)
    {
        if (gcd(n, i) == 1)
        {
            phi++;
        }
    }
    return phi;
}
