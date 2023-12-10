// Zadanie 1, main.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

int main(void)
{
    palindrom("kajak") ? printf("Tak\n") : printf("Nie\n");
    palindrom("palindrom") ? printf("Tak\n") : printf("Nie\n");
    palindrom("kobylamamalybok") ? printf("Tak\n") : printf("Nie\n");
}
