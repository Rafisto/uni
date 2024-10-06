#include <stdio.h>
#include <math.h>

int f(int x)
{
    if (x % 2 == 0)
        return x / 2;
    else
        return f(f(3 * x + 1));
}

int main(void)
{
    // for (int i = 1; i <= 10; i++)
    //     printf("f(%d)= %d\n", i, f(i));
    // (2i + 1) 2^k - 1 = 2i*2^k liczby większe od 2k + (2^k - 1) - końcowe jedynki
    // i * 2^{k+1} + (2^k - 1) - k jedynek
    for (int k = 0; k <= 10; k++)
    {
        for (int i = 0; i <= 10; i++)
        {
            prinf("k=%d i=%d :: %d", k, i, );
        }
    }
    return 0;
}
