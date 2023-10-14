#include <stdio.h>

int main(void){
    printf("Triangle. Specify row count: \n");
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int spaces = (n-1) - i;
        int stars = 2 * i + 1;
        for (int j = 0; j < spaces; j++){
            printf(" ");
        }
        for (int j = 0; j < stars; j++){
            printf("*");
        }
        printf("\n");
    }
}