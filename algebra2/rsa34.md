## RSA 34

Dane, liczby pierwsze `p`, `q`, modulus `N`: 
- N = 101080891
- p = 2062465
- q = 101080891

Zgadnijmy klucz prywatny dla małych liczb:
- `p` i `q` są małe, więc `phi(N) = (p-1)(q-1)` jest małe
- `e` jest małe, więc `d` jest małe

## Część pierwsza - złamanie klucza prywatnego

Wykonajmy bruteforce $1<d<\phi(N)$:
- Warunek - wszystkie odkodowane znaki są poprawne:
    - $c^d = m$ (wiadomość znaku UTF-8)
- Osiągnięty dla $d=2062465$

Wiadomość:
> Deep Though znalazł odpowiedź i brzmi ona: 42

## Część druga - rozkład liczby N

Zauważmy, że $101080891 = 10009 \times 10099$

## Częśc trzecia - klucz publiczny

Wyznaczmy $e$:<br/>
- Policzmy $\phi(N)=101060784$.
- Wyznaczmy $e = d^{-1} \mod \phi(N)$.

## Pytanie
Czy można złamać ten klucz analitycznie?