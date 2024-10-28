# Zadanie 1

Zamienić liczby dziesiętne −32, −109 i +127 na postać dwójkową liczb 8-
bitowych w uzupełnieniach U1 i U2.

- [System uzupełnieniowy U1](https://en.wikipedia.org/wiki/Ones%27_complement)
- [System uzupełnieniowy U2](https://en.wikipedia.org/wiki/Two%27s_complement)

Dec to U1 - Convert to binary, if negative invert all bits

- $-32$ = `U1` 1101 1111 = inv (0010 0000)\_{2}, 1101 1111 (-127 + 64 + **0** + 16 + 8 + 4 + 2 + 1)
- $-109$ = `U1` 0110 1101 = inv (1001 0010)\_{2} (-127 + 16 + 2)
- $+127$ = `U1` 0111 1111 (64 + 32 + 16 + 8 + 4 + 2 + 1)

U1 [-127, 127] -> ostatni bit jest ujemny, wtedy $1111111_{U1} = 0$

Dec to U2 - if positive, convert to binary and if negative, add 2^8 to the number and convert to binary

U2 [-128, 127] -> ostatni bit jest ujemny, wtedy $11111111_{U2} = -1$

- $-32$ = `U2` 1110 0000 = -32 + 2^8 to bin
- $-109$ = `U2` 1001 0011 = -109 + 2^8 to bin
- $+127$ = `U2` 0111 1111 (64 + 32 + 16 + 8 + 4 + 2 + 1)

Zapiszmy (-7) w U1, U2 4-bitowym.

$-7 -> -0007 -> -0101 -> 1010_{U1}$  
$-0101 -> (1010 + 1)_{U2} = (1011)_{U2}$  
$Q = 1111$

Zapiszmy (-7) w U9 4-bitowym;

$-7 -> -0007 -> (9992)_{U9} = (9992+1)_{U10} = (9993)_{U10}$

# Zadanie 2

Zamień liczby $(-011011)_2$, $(101110)_2$, $111000_{U1}$ na postać $4$-cyfrowych liczb
dziesiętnych w uzupełnieniach $U_9$ i $U_{10}$.

Dec to 4 cyfrowe U9 - Convert to decimal, if negative invert all bits

a) $(-011011)_2 = (-27)_{10} = (10^4 - 27 -1)_{U9} = (9972)_{U9}$  
b) $(101110)_2 = (46)_{10} = 0046_{U9}, 0046_{U10}$  
c) $(111000)_{U1} = (-7)_{10} = (10^4 - 7 - 1)_{U9} = (9992)_{U9} = (9993)_{U10}$

Dec to 4 cyfrowe U10 - if positive, convert to decimal and if negative, add 10^4 to the number and convert to decimal

# Zadanie 3

Wykonaj poniższe odejmowania na 8-bitowych liczbach binarnych przy użyciu
uzupełnienia U1 i U2:
a) 11010 − 1101
b) 11010 − 10000
c) 10010 − 10011
d) 100 − 110000

a) U1: $11010 -> 0001 1010_{U1}$, U2: $11010 -> 0001 1010_{U2}$  
U1: $-1101 -> 1111 0010_{U2}$, U2: $-1101 -> 1111 0011_{U2}$

```bash
# odejmowanie w U1 (dodawanie po zamianie)
# przeniesienie w U1 jest dodawane jako 1 na końcu
 00011010
+11110011
---------
 00001100
+       1
---------
 00001101
```

```bash
# odejmowanie w U2 (dodawanie po zamianie)
# przeniesienie w U2 jest ignorowane
# uwaga przepełnienie: dodawanie dwóch dużych liczb zwróci liczbę ujemną - czyli błąd
 00011010
+11110011
---------
 00001101
```

Albo rozszerzamy zakres albo można strzelić sobie w łeb.

b)

```bash
# U1
 00011010
+11101111
---------
 00001001
        1
---------
 00001010 (10)U1
```

```bash
# U2
 00011010
+11101111
---------
 00001001 (10)U2
```

c)

```bash
# U1
 00011010
+11101100
---------
 11111110 (-1)U1
```

```bash
# U2
 00011011
+00010010
---------
 11111111 (-1)U2
```

d)

```bash
# U1
 00000100
+11001111
---------
 11010011 (-92)U1>
```

```bash
# U2
 00000100
+11010000
---------
 11010100 (-92)U2
```

# Zadanie 4

Wykonaj poniższe odejmowania na 5-cyfrowych liczbach dziesiętnych przy
użyciu uzupełnienia U9 i U10:
a) 324-128
b) 100-224
c) 1024-1020

a) 

$324_{10} -> 00324_{U9} = 00324_{U10}$  
$-128_{10} -> 99871_{U9} = 99872_{U10}$  

```bash
# U9
 00324
+99871
------
 00195
     1
------
 00196
```

```bash
# U10
 00324
 99872
------
 00196
```

b)

$100=00100_{U9}$  
$-224=99775_{U9}$  

```bash
#U9
 00100
+99775
------
 99875 (U9) = 99876 (U10)
```

c)

$01024 - 01020$  
$-01020 = (98979)_{U9} = (98980)_{U10}$  

```bash
#U9
 01024
+98979
------
 00003
     1
------
     4
```


```s
|---|----|
0   x_1  x_2

x_2 - x_1 to odległość odcinka x_1 x_2
```

```s
         |-----(R-128)-----------|
|--------|-------|---------------|--g---|
0        128     324             R
                 
         |--g----|---------(R-128)------|

# Widzimy że mamy na myśli to samo g
```


```bash
\beta -> pełny U"\beta"
      -> niepełny U"{\beta-1}"

(Q)_{8} = {8,8,8,...}
-126 = (762)_{U7}, (763)_{U8}
```

# Zadanie 5

Pokaż, że poniższy sposób wyznaczania liczby przeciwnej w U2 jest
równoważny metodzie negacji bitów i dodania jedynki:

1. Przejść do pierwszego od prawej strony bitu zapisu liczby,
2. Przepisywać kolejne bity 0, aż do napotkania bitu o wartości 1, który również
   przepisać,
3. Wszystkie pozostałe bity przepisać, zmieniając ich wartość na przeciwną.

```bash
01100
10100
  011
    1
-----
  100
```



# Zadanie 6

Znakowe rozszerzenie liczby w U1 i U2 polega na powieleniu najstarszego bitu na
wszystkie dodane bity np.
a) $0101_{U2} = 00000101_{U2} = 000000101_{U1}
b) $1001_{U2} = 11111001_{U2} = 11111001_{U1}
Pokaż, że znakowe rozszerzenie liczby w U2 nie zmienia jej wartości.

Powielmy ostatni bit na dodane bity:

Dla 0 - nic się nie zmienia
Dla 1 - dodajemy n-jedynek, zobaczmy dodając `m` jedynek z przodu uzyskujemy

$s = -2^{m+n} + \sum_{k=0}^{m} 2^{m+n-1} = -2^{n}$

# Zadanie 7

Wykonaj mnożenie następujących liczb binarnych w U1 i U2:
a) 1101 · 1101
b) 1101 · 1000
c) 1001 · 1011
d) 100 · 11000
e) 101010 · 011110

# Zadanie 8

Przeanalizuj oraz wytłumacz zasadę działania algorytmu mnożenia liczb
binarnych w U2 metodą Bootha. Następnie wykonaj tą metodą mnożenie
następujących liczb w U2:
a) 101010 · 011110
b) 101010100 · 011111110
c) 0101010100 · 1111111110

# Zadanie 9

Pokaż, jak ustawione są bity C (przeniesienia) i V (nadmiaru) dla podanych liczb
binarnych po operacji odejmowania. Pokaż jednocześnie interpretacje w NKB
oraz U2.
a) 00100001 − 10010100
b) 10100011 − 00110101
c) 10001100 − 10000001
d) 10000010 − 10010110

# Zadanie 10

Znajdź przedstawienie (w postaci liczby binarnej) następujących liczb
zmiennoprzecinkowych w standardzie IEEE-754 pojedynczej precyzji
a) 120,45
b) 1000000,123
c) −0,0045
d) 1023,43

# Zadanie 11

Jaki jest zakres i rozdzielczość liczb dodatnich zapisanych w formacie
IEEE-754 pojedynczej precyzji? Uzasadnij.

# Zadanie 12

Dla formatu „zapisu inżynierskiego”: ∓{0-9}{0-9}.{0-9}⨯10∓{0-9}
wykonaj dodawania: 5/1000 + 1/100 i 5/1000 + 1/10
