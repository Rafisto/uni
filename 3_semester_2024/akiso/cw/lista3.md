# Zadanie 1

Zamienić liczby dziesiętne −32, −109 i +127 na postać dwójkową liczb 8-
bitowych w uzupełnieniach U1 i U2.

- [System uzupełnieniowy U1](https://en.wikipedia.org/wiki/Ones%27_complement)
- [System uzupełnieniowy U2](https://en.wikipedia.org/wiki/Two%27s_complement)
 
$-32$ = `U1` 11011111 (-127 + 64 + **0** + 16 + 8 + 4 + 2 + 1)
$-109$ = `U1` 10010010 (-127 + 16 + 2)
$+127$ = `U1` 01111111 (64 + 32 + 16 + 8 + 4 + 2 + 1)

$-32$ = `U2`

# Zadanie 2

Zamień liczby (-011011)2, (101110)2, 111000U1 na postać 4-cyfrowych liczb
dziesiętnych w uzupełnieniach U9 i U10.

# Zadanie 3

Wykonaj poniższe odejmowania na 8-bitowych liczbach binarnych przy użyciu
uzupełnienia U1 i U2:
a) 11010 − 1101
b) 11010 − 10000
c) 10010 − 10011
d) 100 − 110000

# Zadanie 4

Wykonaj poniższe odejmowania na 5-cyfrowych liczbach dziesiętnych przy
użyciu uzupełnienia U9 i U10:
a) 324-128
b) 100-224
c) 1024-1020

# Zadanie 5

Pokaż, że poniższy sposób wyznaczania liczby przeciwnej w U2 jest
równoważny metodzie negacji bitów i dodania jedynki:
1. Przejść do pierwszego od prawej strony bitu zapisu liczby,
2. Przepisywać kolejne bity 0, aż do napotkania bitu o wartości 1, który również
przepisać,
1. Wszystkie pozostałe bity przepisać, zmieniając ich wartość na przeciwną.

# Zadanie 6

Znakowe rozszerzenie liczby w U1 i U2 polega na powieleniu ostatniego bitu na
wszystkie dodane bity np.
a) 0101U2 = 00000101U2 = 000000101U1
b) 1001U2 = 11111001U2 = 11111001U1
Pokaż, że znakowe rozszerzenie liczby w U2 nie zmienia jej wartości.

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