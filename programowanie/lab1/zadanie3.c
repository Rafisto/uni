#include <stdio.h>

int main(void)
{
    printf("Create a rectangle of size n x 2n. Specify n\n");
    int n;
    scanf("%d", &n);
    if (n < 1 || n > 20) {
        printf("n must be between 1 and 20\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        for(int i = 0; i < 2*n; i++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}