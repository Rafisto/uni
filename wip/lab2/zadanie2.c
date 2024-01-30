// Zadanie 2, zadanie2.c Rafał Włodarczyk
#include <stdio.h>

int main(void){
    double sum = 0;
    int n = 0;
    while (sum <= 10){
        n++;
        sum += 1.0/(double)n;
    }
    printf("%d\n", n);
}
