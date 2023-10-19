#include <stdio.h>
#include <math.h>

int main(void){
    double mul = 1;
    for (int x = 1; x<= 1000; x++) {
        mul *= pow(x,(1.0/1000.0));
    }
    printf("Approximated: %lf\n",mul);
}
