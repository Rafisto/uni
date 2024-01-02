// Zadanie 2, decoder.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

void generateCombinations(int set[1296][4])
{
    int ctr = 0;
    for (int i = 1; i <= 6; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            for (int k = 1; k <= 6; k++)
            {
                for (int l = 1; l <= 6; l++)
                {
                    set[ctr][0] = i;
                    set[ctr][1] = j;
                    set[ctr][2] = k;
                    set[ctr][3] = l;
                    ctr++;
                }
            }
        }
    }
}

int possible = 1296;
int guess()
{
    int set_of_combinations[1296][4];
    generateCombinations(set_of_combinations);

    while (possible > 0)
    {
        printf("I have %d possibilities left.\n", possible);

        int code_guess[4];
        for (int i = 0; i < 4; i++)
        {
            code_guess[i] = set_of_combinations[0][i];
        }

        Result result = check_code(code_guess);

        if (result.red == 4)
        {
            printf("I guessed it!\n");
            return 0;
        }

        int new_possible = 0;

        for (int i = 0; i < possible; i++)
        {
            if (check(code_guess, set_of_combinations[i]).red == result.red && check(code_guess, set_of_combinations[i]).white == result.white)
            {
                for (int j = 0; j < 4; j++)
                {
                    set_of_combinations[new_possible][j] = set_of_combinations[i][j];
                }
                new_possible++;
            }
        }

        possible = new_possible;
    }
    printf("You might be cheating!\n");
    return 0;
}
