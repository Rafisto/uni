### Czytanie programu

`a.out`:
- text
- rodata - dane statyczne
- data - 
- bss 
- (*) stack - najszbszy i preferowany
- heap (malloc) - może zajść wyciek pamięci
    - do danych użytkownika nieznanych rozmiarów
    - obiekt zmienia się w trakcie działania programu

### Program

```c
int add(int a, int b) {
    int c = a + b;
    return c;
}

int main(void) {
    int x = 5;
    int y = 10;

    int z = add(x,y);
    printf("%d + %d = %d",x,y,z);
    return 0
}
```

### Wykonanie programu

Funkcja `main` zaczyna się:

```
początek stosu
___
___
koniec stosu
```

Stos:
- kładzie na góre, ściąga z góry
- może zobaczyć dowolny element

Powyższy program alokuje następujące zmienne. Kładziemy zmienne:
```
początek stosu
___ <- stack pointer (CPU)
[+] z <- zauważmy, że sp[-1] = z
[+] y
[+] x
___
koniec stosu
```

Kładziemy wartości zmiennych:
```
początek stosu
___
[ ] z 
[+] y = 10
[+] x = 5
___
koniec stosu
```

Rekordy aktywacji (dawna idea) - dla każdej funkcji alokuje:
- [RET] Adres powrotu po wykonaniu funkcji
- [ADD_A] Zmienne wejścia
- [ADD_B] Zmienne wejścia
- [ADD_C] Zmienne wewnątrz-funkcyjne

Kładziemy funkcje `add(x,y)` na stosie
```
początek stosu
___
[+] c
[+] function_ret
[+] y_temp = y
[+] x_temp = x
[ ] z 
[ ] y = 10
[ ] x = 5
___
koniec stosu
```

Funkcja wie ile ma parametrów.

Wykonujemy funkcje:
```
początek stosu
___
[-] c = 15
[-] function_ret
[-] y_temp = y
[-] x_temp = x
[+] z 15 
[ ] y = 10
[ ] x = 5
___
koniec stosu
```

Przejście Registry
```
c = 15 -> eax = 15 -> z
```

Wykonajmy printf:
Wykonujemy funkcje:
```
początek stosu
___
[+] printf
[+] ptr_to_("%d + %d = %d")
[+] y_print
[+] x_print
[ ] z 15 
[ ] y = 10
[ ] x = 5
___
koniec stosu
```

Funkcja `main` kończy się:

```
początek stosu
___
___
koniec stosu
```

```c
void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}
```

Ze względu na działanie stacka - po skończeniu funkcji dane tymczasowe:
    - `x_temp`, `y_temp` zostają usunięte, więc wartości spoza funkcji nie ulegną zmianie.

Weźmy punkt 2D:
```c
int p[2];
```

Weźmy 10 punktów 2D
```c
int p[10][2];
```

Stwórzmy strukturę punkt:
```c
struct Point2D
{
    int x;
    int y;
    char* name; // pointer -> prawdopodobnie dynamiczna pamięć
}; // w tym momencie kompilator musi znać rozmiar struktury

struct Point2D P;
```

Wpiszmy dane w obiekt:
```c
int x,y;
scanf("%d %d", &x, &y);

struct Point2D punkt;
punkt.x = x;
punkt.y = y;

punkt.name = malloc(...);
// write char array
```

Stwórzmy funkcje drukującą punkt:
```c
void Point2D_print(const struct Point2D* p) 
{
    // print point
}
```

Stworzyliśmy pseudoobiekt.
- W `C` przyjęło się, że nazwy funkcji danę struktury zawierają prefiks - jej nazwę:
```c
struct Point2D {
    // definition
}
struct Point2D_print {
    // related to Point2D 
}
```
