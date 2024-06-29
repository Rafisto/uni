// Zadanie 1, zadanie1.c Rafał Włodarczyk
#include <stdio.h>

int main(void){
    int R; 
    printf("Wprowadź rok:\n");
    scanf("%d",&R);
    
    if ((R % 400 == 0) || (R % 4 == 0 && R % 100 != 0)) {
        printf("Rok %d jest przestępny.\n",R);
    }
    else{
        printf("Rok %d nie jest przestępny.\n", R);
    }

    return 0;
}
