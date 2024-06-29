#include <stdio.h>


int main(void) {
    // initialization
    int x = 17, y = 13;
    printf("x = %d, y = %d\n", x, y);
    // method 1 - temp variable
    int x0 = x;
    int y0 = y;
    int temp = x0;
    x0 = y0;
    y0 = temp;
    printf("x = %d, y = %d\n", x0, y0);

    // method 2 - substraction
    int x1 = x;
    int y1 = y;
    x1 = x1 + y1;
    y1 = x1 - y1;
    x1 = x1 - y1;
    printf("x = %d, y = %d\n", x1, y1);

    // method 3 - xor
    int x2 = x;
    int y2 = y;
    x2 = x2 ^ y2;
    y2 = x2 ^ y2;
    x2 = x2 ^ y2;
    printf("x = %d, y = %d\n", x2, y2);
}