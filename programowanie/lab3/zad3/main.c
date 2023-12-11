// Zadanie 3, main.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

int main(void)
{
    printf("Euler totient function\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("phi(%d) = %d\n", i, phi(i));
    }
}
