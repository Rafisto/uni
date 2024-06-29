# Zagadnienia na II kolokwium - Algebra 1

## Przestrzenie liniowe
- Sprawdź czy $A=\{...\}$ jest podprzestrzenią $\mathbb{R}^3$
- Sprawdź czy $B=\{b_1,...,b_n\}$ jest bazą
- Podaj bazę i wymiar $V=\{(x,y,z,t): x+2t=0\}$

## Funkcje liniowe
- Czy $f(x,y,z)=$ wzór jest liniowa - jeśli jest podaj jej macierz
- Niech $f: V\rightarrow W$ - funkcja liniowa $B_1,B_2$ - bazy. Wyznacz macierz $f$ w bazach $B_1, B_2$
- Wyznacz wzór $f$ lin. znając $f(1,2)=(3,4)$, $f(5,6)=(7,8)$
- W jakiej bazie wykonanie działania jest proste - wektory bazy $45\degree$ od normalnej do odbijania wzgl. $f(x)=x$

## Macierze
- Dodawanie, odejmowanie, mnożenie
- Macierz odwrotna
- Wyznacznik macierzy - **eliminacja Gaussa** (z wykładu)
- Wyznacznik macierzy - **rozwinięcie Laplace'a**. Przypominajka - rekurencyjnie:
    - $\det [a_{11}] = a_{11}$
    - $\det (A) = \sum_{j=1}^{n} a_{ij} \cdot (-1)^{i+j} \cdot \det A_{ij}$, gdzie $A_{ij}$ - minor macierzy
- Odwrócić macierz

## Wzory
- $\det (A\cdot B) = \det(A) \cdot \det(B)$ - homomorfizm 
- $\det (A^n) = (\det(A))^n$
- $\det (A^{-1}) = (\det(A))^{-1}$
- Zadanie: oblicz $\det(A^5\cdot B^{-3}\cdot A^{-4}\cdot B^4)=$<br/>
$=\det(A^5)\cdot\det(B^{-3})\cdot\det(A^{-4})\cdot\det(B^{4})=$<br/>
$=\det(A) \cdot \det(B)$

## Odwracanie macierzy
$A\cdot A^{-1} = Id.$
$A=?$
$[A|I] \rightarrow [I|A']$

## Układy równań
- Metoda eliminacji Gaussa
- Metoda wyznacznikowa - równania $n\times n$ - dla $n$ równań i $n$ zmiennych

## Wektory własne i wartości własne macierzy (kwadratowej)
Niech $A\in K^{n\times n}$. Jeśli $\lambda\in K$ - skalar, $v\in K^{n}, v\neq 0$ spełnia:<br/>
$A\cdot v = \lambda \cdot v$<br/>
Wtedy $v$ to wektor własny a $\lambda$ to wartość własna macierzy. $v || \lambda v$. <br/> 
Uwaga jeśli $A$ to obrót o kąt $\alpha$ - ta macierz nie posiada wektorów własnch.<br/><br/>

1. Wartości własne to takie $\lambda$, że:<br/>
$\det(A-\lambda I) = 0$<br/>
Niech $\lambda_1, \lambda_2, ... \lambda_n$ - wartości własne<br/>

2. Wektory własne i dla każdej w.w $\lambda_i$:<br/>
$A\cdot v = \lambda_i \cdot v$ <- szukamy v

## Ortogonalizacja Grama - Schmidta

Dana $V$ nad $\mathbb{R}$ oraz baza $B=\{b_1,b_2,...,b_n\}$.<br/>
Ortogonalizacja GS robi nową "lepszą" bazę $B\rightarrow A=\{a_1,a_2,...,a_n\}$:
- $|a_i| = 1$
- $a_i$ prostopadła do $a_j$ dla $i\neq j$

Baza ortonormalna<br/>

Zastosowania:
- prosta najlepszego dopasowania:
    - regresja liniowa 
    - metoda najmniejszych kwadratów