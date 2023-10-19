#include <stdio.h>

#define range 1000

int results[range];
int main(void)
{
    for (int i = 1; i <= 1000; i++)
    {
        int divisors = 0;
        for (int j = 1; j < i; j++){
            if (i % j == 0){
                divisors+=j;
            }
        }
        results[i]=divisors;
        if (results[i] == i) {
            printf("%d to liczba doskonała\n", i);
        }
        
        for (int j = 1; j < i; j++){
            if (results[i] == j && results[j] == i) {
                 printf("(%d, %d) to liczby zaprzyjaźnione\n", j, i);
            }
        }
    }
}