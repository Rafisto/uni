$a+bc=(a+b)(a+c)$ (przydatne w zad. 3)

## Zadanie 3

Przedstaw za pomocą SOP (sum of products)

- SOP: $D(A'+B) + B'D = DA' + DB + B'D = DA' + D(B+B') = DA' + D = D(A'+1) = D$
- POS: $D(A'+B) + B'D = D(A'+B+B') = ...$

- SOP: $Y'Z + WXY' + WXZ' + W'X'Z = Y'Z + WXY' + (WXZ' + W')(WXZ' + X'Z)$ (masakra)
  
## Zadanie 4

Są swoim bezpośrednim przeciwieństwem:
- `minterm` - m - $f(x,y,z)=1$
- `Maxterm` - M - $f(x,y,z)=0$

$(0,0,1), (0,1,1), (1,1,1)$

$f(x,y,z) = \sum\, m(1, 3, 7) = X'Y'Z + X'YZ + XYZ = \Pi\, M(0,2,4,5,6)$

$m_i$ jest stałe dla zmiennych XYZ: $X'Y'Z=m_1, XYZ'=m_6, X'YZ'=m_2,XY'Z=m_5$

$(0,0,1), (0,1,1), (1,1,0), (1,1,1)$

$f(x,y,z) = \Pi\, M(0, 3, 6, 7) = X'Y'Z' * X'YZ * XY'Z' * X'Y'Z'$

Negacje:

$H'=m_0+m_5=X'Y'Z' + XY'Z$

$H=(X'Y'Z' + XY'Z)'=(X'Y'Z')'(XY'Z)'=(X+Y+Z)(X'+Y+Z')=M_0*M_5$

$F*H = \Pi\,M(0,2,4,5,6) * \Pi\,M(0,5) = \Pi\,M(0,2,4,5,6)$

## Zadanie 5

a) $F = XY + X’Y’ + Y’Z$, AND, OR, NOT (easy)

c) $F = ((XY+X'Y'+Y'Z)')' = ((XY)'(X'Y')'(Y'Z)')'$ (De Morgan)

## Zadanie 6

a) $P’ + P’R + QR = P'(1+R)+QR' = P'*1 + QR' = P' + QR' = (P'+Q)*(P'+R')$

Kanonicznie $P'+QR' = P' + PQR' + P'QR' = P'QR + P'QR' + P'Q'R + P'Q'R' + PQR'$

Kanonicznie $P'+QR' = (P'+Q+RR')(P'+R+QQ')=(P'+Q+R)(P'+Q+R')(P'+R+Q')$

## Zadanie 7

Parzysta:
- ostatni bit

Pierwsza:
- ?

- SOP: $XY + XZ' + Y'Z$
- POS: $(X+Y')(Z'+Y)(X+Y)
~ XY + (A+B)X + Z'

Postaci kanoniczne to POS / SOP

$Y'\equiv\overline(Y)$

