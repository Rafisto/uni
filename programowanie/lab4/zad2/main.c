// Zadanie 2, main.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

Result check_code(int *array)
{
    Result result = {0,0};
    printf("[%d] [%d] [%d] [%d]?\n", array[0], array[1], array[2], array[3]);
    printf("red: ");
    scanf("%d", &result.red);
    printf("white: ");
    scanf("%d", &result.white);
    return result;
}

int main(void)
{
    guess();
}
