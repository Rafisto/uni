> ja lektur nie czytałem.<br/>
> potop - gruba książka, męcząca oczy.

## Zadanie 1

Pokaż że jeśli $|X|=n$ to $|P(x)|=2^n$.

Dla $n = 0$, zbiór $X$ jest pusty, więc zbiór potęgowy $P(X)$ zawiera tylko jeden element, czyli zbiór pusty. Zatem $|P(X)| = 2^0 = 1$.

**Krok indukcyjny:**
Załóżmy, że dla pewnego $n$, $|X| = n$, to $|P(X)| = 2^n$.

Rozważmy zbiór $X_{n+1}=X_{n} \cup \{x\}$ o mocy $n+1$, tj. $X$ oraz $\{x\}$ są rozłączne. Wybierzmy dowolny element $x\in X$. Możemy podzielić zbiór $P(X)$ na dwa podzbiory: te, które zawierają x i te, które go nie zawierają.

Pierwszy podzbiór zawiera wszystkie podzbiory X, które nie zawierają x. Jest to $P(X_n)=2^n$.

Drugi podzbiór zawiera wszystkie podzbiory X, które zawierają x. Również jest mocy $|P(X_n)|=2^n$


Sumując te dwa podzbiory, otrzymujemy $|P(X_{n+1})| = 2^n + 2^n  = 2^{n+1}$

Zatem dla dowolnego $n$, jeśli $|X| = n$, to $|P(X)| = 2^n$.

## Zadanie 2

Pokaż, że liczba permutacji zbioru n-elementowego jest równa $n!$.

Dla $n = 1$, zbiór składa się z jednego elementu, więc liczba permutacji wynosi $1! = 1$.

**Krok indukcyjny:**
Załóżmy, że dla pewnego $n$, liczba permutacji zbioru $n$-elementowego wynosi $n!$.

Rozważmy zbiór $X$ o mocy $n+1$. Wybierzmy dowolny element $x$ z $X$. Możemy umieścić x na pierwszej pozycji w permutacji, co daje nam $n!$ możliwości. Na pozostałych n pozycjach możemy umieścić pozostałe n elementów zbioru X, co daje nam $(n+1) \cdot n!$ możliwości.

Zatem dla dowolnego $n$, liczba permutacji zbioru $n$-elementowego wynosi $n! \cdot (n+1) = (n+1)!$.

Stąd wynika, że liczba permutacji zbioru $n$-elementowego jest równa $n!$.

## Zadanie 3

Pokaż że dla zdefiniowanej funkcji $a(n)=0$ dla $n=0$ oraz $a(n) = 2n-1 + a_{n-1}$ dla $n>0$, zachodzi $a(n) = n^2$.

Dla $n = 0$, $a(0) = 0^2 = 0$, co jest zgodne z definicją funkcji.

**Krok indukcyjny:**
Załóżmy, że dla pewnego n, a(n) = n^2.

Rozważmy $a_{n+1}$:<br/>
$a(n+1) = 2(n+1) - 1 + a_n=$<br/>
$= 2n + 2 - 1 + n^2=$<br/>
$= 2n + n^2 + 1=$<br/>
$= (n+1)^2$<br/>

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
int f(int x)
{
    if(x == 0 || x == 1)
        return 1;
    else
        return f(x - 1) + f(x - 2);
}
// ciąg fibbonacciego
int g(int x)
{
    if(x == 0 || x == 1)
        return 1;
    else
        return 2 * g(x - 2);
}
// wykładnicza, jakaś 2^{x/2}
```
$f$ co najmn. 1, $f$ niemalejąca , $f(x+1)\geq f(x) + 1$<br/>
$g\leq f (\forall_x)$. Dla $0,1$ - trywialne.<br/>
Weźmy $g(x)$ dla $x>1 \implies g(x)=2\cdot g(x-2)$... wyjdzie   

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

> Dziwna ta funckja $g$

Pokażmy, że $f(x) = g(x, 0, 1)$ dla $x\geq 0$.

Zastosujemy indukcje po różnicy $x-y$.<br/>
Czym jest $g(x,y,z)=?$ dla $x\geq y$

$g(x,y,z)=z \prod_{i=y+1}^{x}i=z\frac{x!}{y!}$

Indukcja po $x>y$.<br/>
$g(x,y+1,(y+1)z)=(y+1)z\cdot \frac{x!}{(y+1)!}=z\cdot \frac{x!}{y!}$

Dla $y=0,z=1$ mamy $g(x,0,1)=x!$.

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

```c
int f(int x) {
    while (x % 2 == 1) {
        x = (3*x+1)/2 // ~ 3/2 x, wykładniczo
    }
    return x/2;
}
```
(każdy ostro malejący ciąg $n$ jest skończony)

Zapiszmy każdą liczbę:
$n = (2i + 1) 2^k - 1 = 2i\cdot 2^k+2^k-1=i\cdot 2^{k+1}+2^k-1$:
- ($2^k - 1$) - końcowe jedynki

Chcemy żeby na końcu nie było jedynki.

Dowód indukcyjny:<br/>
Dla dowolnego $i$, indukcja po $k$.

Podstawa indukcji ($k=0$):
Dla $k=0$, liczba $(2i+1)2^k - 1$ jest parzysta, a zatem $F((2i+1)2^k - 1) = ((2i+1)2^k - 1)/2$ kończy się, spełniając warunek podstawowy.


Krok indukcyjny ($k > 0$):
Załóżmy, że dla pewnej dowolnej dodatniej liczby całkowitej $m$, $F((2i+1)2^m - 1)$ kończy się. Teraz rozważmy przypadek, gdy $m + 1$:

$F((2i+1)2^{m+1} - 1)$ (nieparzysta a zatem)

$= F(F(3((2i+1)2^{m+1} - 1) + 1))$

$= F(F(3(2i+1)2^{m+1} - 2))$ (parzysta więc // 2)

$= F((2(3i+1) + 1)2^{m} - 1)$

Z założenia indukcyjnego wiemy, że 
$$F((2i+1)2^m - 1)$$
kończy się dla dowolnego $i$. <br/> 
Zatem kończy się również dla $j=3i+1$:<br/>
$$F((2j + 1)2^{m} - 1)$$

Zatem funkcja kończy się dla dowolnego $k _\square$

Malejące w kolejnych iteracjach:<br/>
$x-(x(x-1)) =$<br/>
Czyli $(x(x-1))$ bez kasuje ostatnie 1-ki<br/>
$x-(x(x-1)) = 2^k-1$ utrzymuje ostatnie 1-ki<br/>

Narzędzia automatycznego dow. twierdzeń widzą, że to jest prawda. ~ Major
