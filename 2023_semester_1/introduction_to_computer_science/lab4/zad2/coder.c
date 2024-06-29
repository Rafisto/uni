// Zadanie 2, coder.c Rafał Włodarczyk

#include "functions.h"
#include <stdbool.h>

Result check(int code[], int guess[])
{
    Result result = {0, 0};
    bool codeMatched[4] = {false};
    bool guessMatched[4] = {false};

    for (int i = 0; i < 4; ++i)
    {
        if (guess[i] == code[i])
        {
            codeMatched[i] = guessMatched[i] = true;
            result.red++;
        }
        else
        {
            for (int j = 0; j < 4; ++j)
            {
                if (!guessMatched[i] && !codeMatched[j] && guess[i] == code[j])
                {
                    codeMatched[j] = true;
                    result.white++;
                    break;
                }
            }
        }
    }

    return result;
}
