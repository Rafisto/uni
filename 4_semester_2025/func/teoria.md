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