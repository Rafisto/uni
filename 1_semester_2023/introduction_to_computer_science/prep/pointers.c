#include <stdio.h>
#include <malloc.h>
#include <assert.h>

int* x;
int* y;
int z;

int main() {
    x = malloc(sizeof(int));
    *x = 10;
    y = x;
    z = *x;
    assert(x == &(*x));
    printf("x(ref) = %p\n", x);
    printf("x(val-ref) = %p\n", &(*x));
    printf("x(val) = %d\n", *x);
    printf("y(val) = %d\n", *y);
    printf("y(ref) = %p\n", y);
    printf("z(val) = %d\n", z);
    printf("z(val-ref)= %p\n", &z);
}

