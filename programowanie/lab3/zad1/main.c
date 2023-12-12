// Zadanie 1, main.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

int main(void)
{
    char* tests[] = {"kajak", "palindrom", "kobylamamalybok"};
    for (int i = 0; i < 3; i++)
    {
        if (palindrom(tests[i]))
        {
            printf("+ %s is a palindrome\n", tests[i]);
        }
        else
        {
            printf("- %s is not a palindrome\n", tests[i]);
        }
    }
}
