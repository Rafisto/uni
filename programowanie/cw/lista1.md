#### Zadanie 1

a)

a | b | c
--|---|---
10 | 20 | 10
10 | 20 | 10
10 | 20 | 5
10 | 20 | 15

b)

a | b | c
--|---|---
40| 10| 0
40| 10| -30
40| 10| -15
40| 10| 25

c)

$c=\frac{b-a}{2} \implies c=a+\frac{b-a}{2} = \frac{2a+b-a}{2} = \frac{a+b}{2}$

Ale co jeśli $a+b$ jest nieparzysta, wtedy aby wynik był zgodny z programem to musi zajść:

$c=floor(\frac{a+b}{2})$

#### Zadanie 2 

a | b | c | d |
--|---|---|---|
5 |  1|  7|  0|
5 |  1|  7|  5| if
5 |  1|  7|  7| 2if

Końcowa zależność:

$d=max(a,b,c)$

### Problem wyboru sekretarki 
Algorytm oceniający, w którym decyzja musi być natychmiastowa. Istnieje algorytm który wybiera dobrą wartość.

Rozwiązanie: Wybierz z iloma kandydatkami będziesz rozmawiał, potem wybierz pierwszą najlepszą z pośród wcześniejszych z którymi rozmawiałeś.

"Ja jestem za stary, niereformowalny" ~ Major

#### Zadanie 3

a | b | c | d |
--|---|---|---|
 3|  6|  5|  0|
 3|  6|  5|  6|
 3|  6|  5|  6|

Końcowa zależność:

$d=max(a,b,c)$

#### Zadanie 4

Metoda ukwadratowiania prostokąta. Założenia: pole = $1\cdot a$, pole zostaje stałe, następnie definiujemy:
- prostokąt $(1, a>0)$
- 2-gi $(\frac{2a}{1+a}, \frac{1+a}{2})$ itd.
- n-ty $(\sqrt{a}, \sqrt{a}$)

x    |   y |
-----|-----|
1.000000| 2.000000
1.000000| 1.500000
1.333333| 1.500000
1.333333| 1.416667
1.411765| 1.416667
1.411765| 1.414216
1.414211| 1.414216
1.414211| 1.414214
1.414214| 1.414214
$\frac{2}{\sqrt{2}}$|$\frac{\sqrt{2}+\sqrt{2}}{2}$

Teza:

$lim_{n\rightarrow \infty} f(x,y) = \sqrt{y}$

D-d:

Metoda babilońska