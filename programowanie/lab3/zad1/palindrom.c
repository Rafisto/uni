// Zadanie 1, palindrom.c Rafał Włodarczyk

#include <stdbool.h>
#include <string.h>

bool palindrom(char napis[])
{
    size_t length = strlen(napis);
    for (size_t i = 0; i < length / 2; i++)
    {
        if (napis[i] != napis[length - i - 1])
        {
            return false;
        }
    }
    return true;
}
