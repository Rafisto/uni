// Zadanie 3, gcd.c Rafał Włodarczyk

int gcd(long int a, long int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}