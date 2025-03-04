### Zadanie 1

```hs
power :: Int -> Int -> Int
power x y = y ^ x

p2 = power 4
p3 = power 3
```

1.1 Wartość wyrażenia:

```bash
ghci> (p2 . p3) 2
4096
```

Wyjaśnienie

1.2 Zbadajmy typy `p2`, `p3` i `(p2 . p3)`

1.3 Zapiszmy lambda wyrażenia:

