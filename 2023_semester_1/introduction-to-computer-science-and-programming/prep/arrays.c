#include <stdio.h>
#include <malloc.h>

int main(void) {
    // part 1 - pointer arithmetic
    int arr[] = {1, 2, 3, 4, 5};
    int x = 2136;
    int* ptr = arr;
    int* xptr = &x;
    printf("arr = %p\n", ptr);
    printf("a = %p\n", xptr);
    printf("arr - a = %ld\n", ptr-xptr);
    printf("a(arr) = %d\n", ptr[-1]);
    // part 2 - memory allocation
    int* arr2_ptr = malloc(sizeof(int)*5);
    int* x2ptr = malloc(sizeof(int));
    for (int i = 0; i < 5; i++) {
        arr2_ptr[i] = i+1;
    }
    *x2ptr = 2137;
    printf("arr2_ptr %p\n", arr2_ptr);
    printf("a2_ptr %p\n", x2ptr);
    printf("arr2 = %d\n", *(arr2_ptr));
    printf("a2 = %d\n", *(x2ptr));
    printf("arr - a = %ld\n", x2ptr-arr2_ptr);
    printf("a(arr) = %d\n", arr2_ptr[8]);
    return 0;
}
