## Zadanie 1

Pokaż że jeśli |X|=n to |P(x)|=2^n.

Dla n = 0, zbiór X jest pusty, więc zbiór potęgowy P(X) zawiera tylko jeden element, czyli zbiór pusty. Zatem |P(X)| = 2^0 = 1.

**Krok indukcyjny:**
Załóżmy, że dla pewnego n, |X| = n, to |P(X)| = 2^n.

Rozważmy zbiór X o mocy n+1. Wybierzmy dowolny element x z X. Możemy podzielić zbiór P(X) na dwa podzbiory: te, które zawierają x i te, które go nie zawierają.

Pierwszy podzbiór zawiera wszystkie podzbiory X, które zawierają x. Zbiór X ma n+1 elementów, więc możemy wybrać x na n+1 sposobów. Zatem ten podzbiór ma 2^n+1 elementów.

Drugi podzbiór zawiera wszystkie podzbiory X, które nie zawierają x. Zbiór X ma n+1 elementów, więc możemy wybrać podzbiór bez x na 2^n sposobów. Zatem ten podzbiór ma 2^n elementów.

Sumując te dwa podzbiory, otrzymujemy |P(X)| = 2^n+1 + 2^n = 2^n _ (1 + 1) = 2^n _ 2 = 2^(n+1).

Zatem dla dowolnego n, jeśli |X| = n, to |P(X)| = 2^n.

## Zadanie 2

Pokaż, że liczba permutacji zbioru n-elementowego jest równa n!.

Dla n = 1, zbiór składa się z jednego elementu, więc liczba permutacji wynosi 1! = 1.

**Krok indukcyjny:**
Załóżmy, że dla pewnego n, liczba permutacji zbioru n-elementowego wynosi n!.

Rozważmy zbiór X o mocy n+1. Wybierzmy dowolny element x z X. Możemy umieścić x na pierwszej pozycji w permutacji, co daje nam n! możliwości. Na pozostałych n pozycjach możemy umieścić pozostałe n elementów zbioru X, co daje nam (n+1) \* n! możliwości.

Zatem dla dowolnego n, liczba permutacji zbioru n-elementowego wynosi n! \* (n+1) = (n+1)!.

Stąd wynika, że liczba permutacji zbioru n-elementowego jest równa n!.

## Zadanie 3

Pokaż że dla zdefiniowanej funkcji a(n)=0 dla n=0 oraz a(n) = 2n-1 + a\_{n-1} dla n>0, zachodzi a(n) = n^2.

Dla n = 0, a(0) = 0^2 = 0, co jest zgodne z definicją funkcji.

**Krok indukcyjny:**
Załóżmy, że dla pewnego n, a(n) = n^2.

Rozważmy a(n+1):
a(n+1) = 2(n+1) - 1 + a(n)
= 2n + 2 - 1 + n^2
= 2n + n^2 + 1
= (n+1)^2

Zatem dla dowolnego n, a(n) = n^2.

## Zadanie 4

Przekształć poniższy kod:

```c
int f(int n)
{
    if(n == 0)
        return 0;
    else
        return n + f(n - 1);
}
```

do postaci ogonowej oraz postaci iteracyjnej.

Postać ogonowa:

```c
int f(int n, int acc)
{
    if(n == 0)
        return acc;
    else
        return f(n - 1, acc + n);
}
```

Postać iteracyjna:

```c
int f(int n)
{
    int acc = 0;
    while(n > 0)
    {
        acc += n;
        n--;
    }
    return acc;
}
```

## Zadanie 5

Przekształć poniższy kod:

```c
int f(int m, int n)
{
    if(n == 0 || m == n)
        return 1;
    else
        return (m * f(m - 1, n - 1)) / n;
}
```

do postaci ogonowej oraz postaci iteracyjnej.

Postać ogonowa:

```c
int f(int m, int n, int acc)
{
    if(n == 0 || m == n)
        return acc;
    else
        return f(m - 1, n - 1, (m * acc) / n);
}
```

Postać iteracyjna:

```c
int f(int m, int n)
{
    int acc = 1;
    while(n > 0 && m != n)
    {
        acc = (m * acc) / n;
        m--;
        n--;
    }
    return acc;
}
```

## Zadanie 6

Udowodnij że jeśli x>=y to f(x) >= f(y) >= 1 oraz f(x) >= g(x).

```c
int f( int x)
{
    if(x == 0 || x == 1)
        return 1;
    else
        return f(x - 1) + f(x - 2);
}
int g( int x)
{
    if(x == 0 || x == 1)
        return 1;
    else
        return 2 * g(x - 2);
}
```

Niech zakresem zmienności będą liczby naturalne.
Pokażmy, że f(x) >= f(y) >= 1 dla x >= y. Założmy że x >= y.

Dla x = 0, f(0) = 1, oraz dla x = 1, f(1) = 1. Zatem f(x) >= 1 dla x = 0, 1.<br/>
Dla każdego kolejnego x > 1, możemy szacować:<br/>
f(x) = f(x - 1) + f(x - 2) >= f(x - 1) >= 1<br/>
Pokażmy że dla x>=y f(x) >= f(y). Załóżmy że x >= y.<br/>
Dla x = 0, f(0) = 1, oraz dla x = 1, f(1) = 1. Zatem f(x) >= f(y) dla x = 0, 1.<br/>
Dla każdego kolejnego x > 1, możemy szacować:<br/>
f(x) = f(x - 1) + f(x - 2) >= f(x - 1)<br/>
f(y) = f(y - 1) + f(y - 2) >= f(y - 1)<br/>
Zatem f(x) >= f(y) dla x >= y. <br/>

## Zadanie 7

```c
int f(int x)
{
    if(x == 0)
        return 1;
    else
        return x * f(x - 1);
}
int g(int x, int y, int z)
{
    if(x == y)
        return z;
    else
        return g(x, y + 1, (y + 1) * z);
}
```

Pokażmy, że f(x) = g(x, 0, 1) dla x >= 0.

Dla x = 0, f(0) = 1, oraz g(0, 0, 1) = 1. Zatem f(0) = g(0, 0, 1).<br/>
Dla każdego kolejnego x > 0, możemy szacować:<br/>
Przyjmijmy założenie indukcyjne, że f(x) = g(x, 0, 1).<br/>
Zobaczmy następnie, że dla:<br/>
f(x + 1) = (x+1) * f(x) = (x+1) * g(x,0,1) = g(x+1,0,1).<br/>

Zatem f(x) = g(x, 0, 1) dla x >= 0.

## Zadanie 8

Udowodnić, że każdy proces spowodowany przez wywołanie f(x), dla naturalnego x, kończy się.

```c
int f(int x)
{
    if(x % 2 == 0)
        return x / 2;
    else
        return f(f(3 * x + 1));
}
```

Rozpiszmy funkcję rekurencyjną:

```c
int f(int x)
{
    if(x % 2 == 0)
    {
        return x / 2;
    }
    else
    {
        if (x % 2 == 0)
            return x / 2;
        else
            return f(3 * x + 1);
    }
}
```

Dowód indukcyjny:

Podstawa indukcji ($k=0$):
Dla $k=0$, liczba $(2i+1)2^k - 1$ jest parzysta, a zatem $F((2i+1)2^k - 1) = ((2i+1)2^k - 1)/2$ kończy się, spełniając warunek podstawowy.

Krok indukcyjny ($k > 0$):
Załóżmy, że dla pewnej dowolnej dodatniej liczby całkowitej $m$, $F((2i+1)2^m - 1)$ kończy się. Teraz rozważmy przypadek, gdy $k = m + 1$:

$F((2i+1)2^{m+1} - 1)$

$= F(F(3((2i+1)2^{m+1} - 1) + 1))$

$= F(F(3(2i+1)2^{m} - 2))$

Ponieważ $(2i+1)2^{m} - 1$ jest liczbą nieparzystą, możemy ją przedstawić jako $(2(3i+1) + 1)2^m - 1$:

$= F((2(3i+1) + 1)2^{m} - 1)$

Teraz, stosując założenie indukcyjne do $F((2(3i+1) + 1)2^{m} - 1)$, dochodzimy do wniosku, że kończy się. Zatem, przez indukcję, udowodniliśmy, że $F(x)$ kończy się dla wszystkich liczb całkowitych $x$, co było naszym celem.