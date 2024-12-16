# Zadanie 1

$M$-bitowy

$k$ jedynek po prawej stronie

$M-k$ zer po lewej stronie

Należy zaprojektować konwerter 3 do 7.
Wykonajmy układ który odejmuje 1 od każdej liczby.

Tabela prawdy dla konwertera 3 do 7:
000 - 0000000
001 - 0000001
010 - 0000011
011 - 0000111
100 - 0001111
101 - 0011111
110 - 0111111
111 - 1111111

```
res = 2^(k) - 1
```