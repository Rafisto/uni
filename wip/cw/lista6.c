#include <stdio.h>

int f(int x)
{
    if(x % 2 == 0)
        return x / 2;
    else
        return f(f(3 * x + 1));
}

int main(void) {
    for (int i = 1; i <= 10; i++)
        printf("f(%d)= %d\n", i, f(i));
    return 0;
}
