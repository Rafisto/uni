Lista rozwiązań:
- [Zadanie 1](#zadanie-1)
- [Zadanie 2](#zadanie-2)
- [Zadanie 3](#zadanie-3)
- [Zadanie 4](#zadanie-4)
- [Zadanie 5](#zadanie-5)
- [Zadanie 6](#zadanie-6)
- [Zadanie 7](#zadanie-7)
- [Zadanie 8](#zadanie-8)
- [Zadanie 9.2](#zadanie-92)

## Zadanie 1

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

p2 (p3 ( 2 )) = (2 ^ 3) ^ 4 = 4096

1.2 Zbadajmy typy `p2`, `p3` i `(p2 . p3)`

```bash
ghci> :t p2
p2 :: Int -> Int
p3 :: Int -> Int
(p2 . p3) :: Int -> Int

ghci> :t (.)
(.) :: (b -> c) -> (a -> b) -> a -> c
```

1.3 Zapiszmy lambda wyrażenia:

```hs
power = \x y -> y ^ x
p2 = \x -> power 4 x
p3 = \x -> power 3 x

p2 = \x -> x ^ 4
p3 = \x -> x ^ 3
(p2 . p3) = \x -> (x ^ 3) ^ 4
```

## Zadanie 2

2. Oblicz w GHCI wartości wyrażeń 2 ∧ 3 ∧ 2, (2 ∧ 3) ∧ 2 i 2 ∧ (2 ∧ 3). Dowiedz się jaka jest łączność oraz siła operatora ∧ za pomocą polecenia :i (∧)

```hs
2 ^ 3 ^ 2 = 512
(2 ^ 3) ^ 2 = 64
2 ^ (2 ^ 3) = 256
```

Siła operatora:

```bash
ghci> :i ^
(^) :: (Num a, Integral b) => a -> b -> a       -- Defined in ‘GHC.Real’
infixr 8 ^ # infix (right-associative) operator with precedence 8 (max is 9)

# ciekawostka - koniunkcja wiąże mocniej niż alternatywa
ghci> :i (&&)
(&&) :: Bool -> Bool -> Bool    -- Defined in ‘GHC.Classes’
infixr 3 &&
ghci> :i (||)
(||) :: Bool -> Bool -> Bool    -- Defined in ‘GHC.Classes’
infixr 2 ||
```

## Zadanie 3

```hs
f::Int -> Int
f x = x ^ 2
g::Int -> Int -> Int
g x y = x+2*y
h :: ...
h x y = f ( g x y )
```

3.1 Jaki jest typ funkcji $h$  - `h :: Int -> (Int -> Int)`

3.2 Czy h = f . g? 

```hs
ghci> :t (f . g)
(f . g) :: (Num a, Num (a -> a)) => a -> a -> a
ghci> :t h
h :: Num a => a -> a -> a
```

## Zadanie 4

Zapiszmy +, * jako lambda-wyrażenia

```hs
add = \x y -> x + y
mul = \x y -> x * y
```

## Zadanie 5

Zapiszmy f (x) = 1 + x ∗ (x + 1), g(x, y) = x + y^2, h(y, x) = x + y^2 jako lambda wyrażenia:

```hs
f = \x -> 1 + x * (x + 1)
g = \x y -> x + y ^ 2
h = \y x -> x + y ^ 2
```

```cpp
auto f = [](int x) -> int { return 1 + x * (x + 1); };
auto g = [](int x, int y) -> int { return x + y * y; };
auto h = [](int y, int x) -> int { return x + y * y; };
```

```js
const f = (x) => 1 + x * (x + 1)
const g = (x, y) => x + y ^ 2
const h = (y, x) => x + y ^ 2
```

```py
f = lambda x: 1 + x * (x + 1)
g = lambda x, y: x + y ** 2
h = lambda y, x: x + y ** 2
```

## Zadanie 6

$curry \circ uncurry$

$curry ( uncurry ( \psi ) (a))(b)$

$\lambda x: A -> (\lambda )$

## Zadanie 7

Przykłady funkcji typów:

```
1. (Int=>Int)=>Int
2. (Int=>Int)=>(Int=>Int)
3. (Int=>Int)=>(Int=>Int)=>(Int=>Int)
```

```hs
f1::(Int->Int)->Int
f1 f = f 0

f1test::(Int->Int)
f1test x = 4

f2::(Int->Int)->(Int->Int)
f2 f = \x -> f x 

f3::(Int->Int)->(Int->Int)->(Int->Int)
f3 f g = \x -> f x + g x
```

## Zadanie 8

## Zadanie 9.2

```hs
g x y = y * y + y + x
f x = g x (sin x)
```
