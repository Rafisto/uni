### 58

```
UP2 (\g -> phi(g*f))
```

## 59

Ustalmy zbiór $A$. Rozważamy odwzorowanie $F_A$ : $Set \rightarrow Set$ określone wzorem $F_A(X)$ =
$A \times X$.
1. Rozszerz odwzorowanie $F_A$ do funktora kategorii $Set$.
2. Zaimplementuj funktor $F_A$ w języku $Haskell$ za pomocą funkcji $((,))$.
3. W zadaniu 6 zdefiniowaliśmy funkcję $uncurry$. Oblicz $uncurry ((,))$.

- F_A(X) = A \times X
- Dla morfizmu f: X->Y zdefiniujmy F_A(f): X x A -> Y x A
Możemy inaczej zapisać: F_A(f) = id_A x f 

F_A(idX)(a,x) = (a,idX(x)) = (a,x) = id(A x X (a,x)) = id_F_A(X)(a,x)
F_A(g circ f) (a,x) = (a, (g circ f)(x)) = F_A(g)(a,f(x))=F_A(g)(F_A(f)(a,x))

2. Haskell Implementation

```hs
data Cart a b = Cart (a,b)
instance Functor (Cart a) where
    fmap f (Cart (x,y)) = Cart(x,(f y))
```
3. Haskell Implementation

```hs
uncarry(,)(a,b) = ((,)a)b = (a,b)
uncarry(,) = id -- pair signature
```

## 60

Maybe a = Nothing | Just a
Maybe (A) = {nothing}+A

[]a = []|a : [a]

<!-- data  Either a b  =  Left a | Right b -->

```hs
>>> let s = Left "foo" :: Either String Int
>>> let n = Right 3 :: Either String Int
>>> either length (*2) s
3
>>> either length (*2) n
6
```

```hs
Either a b = Left a | Right b
Either () a = Left () | Right a

n(Just a) = Right a
n(Nothing) = Left ()
```

## 61

```hs
data T1 a b c = TT1 ( b => a , c => a )
data T2 a b c = TT2 ( Either b c ) => a
```

```hs
A^(B+C) iso A^B x A^C  
```

```hs
t21 (TT2 f) = TT1 (
    (\x -> f(Left x)),
    (\x -> f(Right x))
)

t12 (TT1 f) = TT2 (
    (\x -> case x of
        Left a -> f(Left a)
        Right b -> f(Right b))
)
```

## 62

..

## 63

