Elementy Teorii Kategorii

Def. Kategoria C:
- mamy obiekty ob(C)
- mamy morfizmy mor(C)
- f in morf(C), dom(f), codom(f) in ob(C)
- mamy złożenia o morfizmów
X -> Y -> Z
   f   g
    g \circ f

złożenie jest łączne

dla każdego X in ob(C)
istnieje id_X: X->X
dokładnie jeden ^^

forall f: X -> Y f circ id_X = f
forall f: X -> Y idY circ f = f

SET obiekty === zbiory
morfizmy === (A,f,B) gdzie f: A-> B jest funkcją

Grp (kategoria group) obiekty === grupy (dowolne)
morfizmy === homomorfizmyg grup (G1,phi,G2), gdzie phi: G1 -> G2 jest homomorfizmem grup

cat(X)
X=(X,\leq) - porządek

obiekty === elementy X
morfizmy === (x -> y === x \leq y) morfizmy to nierówności.

Obiekt c jest końcowy w C ===

forall X in ob(C) exists! f  f : X -> c
SET końcowe === jednoelementowe

def d jest porządkiem === forall X exists! f f: d-> X
SET pocz === emptyset || Haskell : typ Void

Jeśli k1, k2 są końcowe to k1 ~izo k2 || Haskell : data () = ().

def. C, D-ustalone kategorie

F: ob(C) -> Ob(D)
F: mor(C) -> mor(D)

jest funktorem jeśli

w kategorii C |= X -f-> Y => D |= F(X) -F(f)-> F(Y)
F(f circ g) = F(f) circ F(g)
F(id_X) = id(F(X))

Przykład
MB::SET->SET
MB(X) = X u {^x} ^x not in X, X neq Y => ^x neq ^y
f: X -> Y
MB(f) = f u {(^x,^y)}

Przykład
Ustalmy A: R_A(X) = X^A : reader
f: X -> Y
R_A (f) :: R_A (X) -> R_A (Y)
R_A (f) :: X^A -> Y^A       A: X -f-> Y
(R_A(f))(phi) = f \circ phi
dla phi in X^A

Przykład
Ustalamy M
W_M(X) = X x M // writer, M-dowolny zbiór // f: X -> Y, W_M(f): X x M -> Y x M
W_M(f) = (x,m) = (f(x),m)


F(f) \approx fmap f
(F(f)) (x) \approx fmap f x

## 13.05.2025

(F, <:>, unit)  unit in F({*})
<:> : F(X) x F(Y) -> F(X x Y)
unit <:> fx ~= fx |
fx <:> unit ~= fx | fx \in F(X)

unit in V2({\*}) = {\*} x {\*} = {(\*,\*)}
<:> : V2(X) x V2(Y) -> V2(X x Y)
(X x X) <:> (Y x Y) -> (X x Y) x (X x Y) : (x1, x2) <:> (y1, y2) = ((x1,y1),(x2,y2))

(x1,x2) ->
(y1,y2) -> ((x1,y1),(x2,y2))

L=((x1,x2) <:> (y1,y2)) <:> (z1,z2) = (((x1,y1),z1),((x2,y2),z2))
P=(x1,x2) <:> ((y1,y2)<:>(z1,z2)) = (((x1,y1),z1),((x2,y2),z2))

alpha ((x,y),z) = (x,(y,z))
alpha_XYZ : (X x Y) x Z -> iso X x (Y x Z)

((V2)(alpha))(L) = P
L({\*}) = {s, [\*], [\*\*], [\*\*\*], ...}

[x1, ..., xn] <:> [y1, ..., ym]
= [(x1,y1), ...(xn,ym)] ++ [(xn,y1) ... (xn,ym)]
= [(x,y) | x <- lx, y <- ly]

<!-- // List comprehension programuje za ciebie -->

zip lx ly:
lx [x1,x2,x3]    -> | -> [(x1,y1),(x2,y2),(x3,y3)] 
ly [y1,y2,y3,y4] -> |

tsip lis

unit = [\*,\*,\*, ...]


W_M (X) = X x M (funktor na tym działa na pierwszą współrzędną.)

Monoid W_M({\*}) = {\*} x M \revin (*, mempty)
(x,m) <:> (y,n) = ((x,y) m<:>n)

ST_S(X) = (X x S)^S
    unit = (\lambda s -> (\*, s))
    phi in (X x S)^S
    psi in (Y x S)^S

((X x Y) x S)^S

(phi <:> psi)(s) = let (x,t) = phi (s), 
                       (y,t) = psi (t)
                   in  ((x,y),r)


1) X - zbiór x \in X

F : Set -funktor-> Set
c_x : {\*} -> x ; c_x = {\*} x {x}
{\*} -c_x-> X     unit \in F({\*})
F({\*}) -F(c_x)-> F(X)     F(c_x) (unit) :: F(x)

pure x = F(\lambda t -> x)(unit)
pure x : X -> F(X)
pure = (pure_X) X\in Ob(Set)

<*> <- apply
<*> :: F(B^A) x F(A) -> F(B)
eval B^A x A -> B : (f,x) -> f(x)

f $ x = f x (ten operator ma zerowy precedence)
fab <*> fa = F(eval) (fab <:> fa)
(F, <*>, pure) <- funktor aplikatywny

Każdy funktor aplikatywny pochodzi z funktora monoidalnego.
Możemy dokonać przekształcenia w dwie strony. 

Przykład (V2)

pure x = V2(\lambda _ -> x) (unit)
       = V2(\lambda _ -> x) (V2(\*,\*))
       // haskell = fmap (\lambda _ -> x) (V2(\*,\*))
       = V2(x,x)

pure x = (x,x)
pure x = V2(x,x)

f \in B^A
g \in B^A

V2(f, g) <*> V2(x,y) =
= (V2(eval))(V2(f,g) <:> V2(x,y)) =
= (V2(eval))(V2((f,x),(g,y))) =
= V2(eval(f,x),eval(g,y)) =
= V2(fx,gy)

(f,g) <*> (x,y) = (f(x),g(x))

Przykład (Listy)

a -> [a]
x \in A : pure x = [x]
[f1,...,fk] <*> [x1,...,xn] = [fx | f <- lf, x <- lx]
 ^^ lf            ^^ lx

liftA2
- mam X
- mam \* : X -> X -> X

F - aplikatywny 
fx, fy \in F(X) 

liftA2 \* fx fy = ((pure(\*) <\*> fx) <\*> fy)

Przykład. F = Maybe
Maybe Double = Double + Nothing

(Just x) + (Just y) = Just (x+y)
Nothing  + _        = Nothing
_        + Nothing  = Nothing

mbPlus (działałoby okej, można to zrobić ręcznie ale to bieda)

mbPlus = liftA2 (+)

liftA2 (lift applicative 2-argument)