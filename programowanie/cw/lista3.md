## zadanie 1

Jak stare wartości spełniają warunek to nowe wartości również spełniają warunek

I 
x=0, y=1, z,i=1
x=1, y=1, z=

Fib(k) = 
```
0 dla k=0
1 dla k=1
Fib(k-1)+Fib(k-2) dla k>1
```

P(x,y,i) = y = Fib(i) oraz x = Fib(i-1)

Warunek niezmiennika pętli
P(x,y,i) AND i<n implies P(x',y',i')

Warunki:
i < n
y = Fib(i)
x = Fib(i-1)
... pętli
z = x + y
x' = y
y' = z
i' = i + 1

Zobaczmy, że:
y' = z = x + y = Fib(i-1) + Fib(i) = Fib(i+1) = Fib(i')
x' = y = Fib(i) = Fib(i'-1)
Dokładnie dwa warunki z definicji niezmiennika pętli

Gdy opuszczamy pętle i=n
Po wyjściu z pętli drukowana jest wartość y = Fib(n)

## zadanie 2

```c
double x = 0;
int i = 0;
while (i < n)
{
x = x + (t[i] - x) / (i + 1) ;
i = i + 1;
}
printf("x = %lf\n" , x);
```

Niezmiennik pętli:
Krok 1-szy:
ix = sum_{j=0}^{i-1} t[j] = P(x,i)

Krok 2-gi:
P(x,i), i<n implies P(x',i')

Warunki:
x' = x + (t[i]-x)/(i+1)
i' = i+1

x'i' = x + (t[i]-x)/(i+1) * (i+1) = x (i+1) + t[i] - x = sum j=0 do i-1 + t[i] = sum j=0 do i = sum j=0 do i-1
Nowe wartości też spełniają warunek

Gdy opuszczamy pętlę i=n a x to średnia arytmetyczna z tablicy.

## zadanie 3

int find1(int x, int n, int t[n]) {
    for (int i = 0; i < n; i++) {
        if (t[i] == x) {
            return i;
        }
    }
    return -1;
}

Potrzeba maksymalnie n iteracji.
Niezmiennik pętli - jeżeli doszliśmy do i, to znaczy że na poprzednich indeksach żadna wartość nie spełnia warunku

## zadanie 4

początkowo 0 do n-1
Dopóki obszar niepusty - sprawdzaj dzieląc przedziały na 2

log2 n - liczba iteracji

## zadanie 5

Scalanie dwóch sortowanych tablic
(wykorzystywane w merge sort)

while i<n j<n:
    if a[i]<b[j]:
        c[i+j]=a[i]
        i++
    else:
        c[i+j]=b[j]
        j++

dopisac tablice

## zadanie 6

- nie wolno sortować tablicy
- raz przejrzeć tablice w czasie liniowym

```c
j=0;k=n-1;i=0;

while(j<=k){
    if(x[j]==y) j++;
    else if(x[j]<y) {
        swap(i,j);
        i++;
        j++;
    }
    else {
        swap(k,j);
        k--;
    }
}
```

Podstawienie `swap`:
```c
swap(i,j) {
    t = x[i];
    x[i] = x[j];
    x[j] = t;
}
```

Niezmiennik. W przedziale x in (0,i-1) x<y, w przedziale x in (i,j-1) x==y, w przedziale x in (k,n-1) x>y.

prywata misrac bezpieczny podzbiór języka C. Narzędzia dowodzące poprawność programów.
`rekurencja` w C jest niebezpieczna.
