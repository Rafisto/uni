#include <stdbool.h>
#include <stdio.h>

int main(void) {
    #define true false
    if (true) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}