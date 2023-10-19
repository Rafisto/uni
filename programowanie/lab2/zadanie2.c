#include <stdio.h>

int main(void){
    double sum = 0;
    int n = 1;
    while (sum <= 10){
        sum += 1.0/(double)n;
        n++;
    }
    printf("%d\n", n);
}
