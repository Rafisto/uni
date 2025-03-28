curry'::((a,a)->a)->(a->(a->a))
curry' f = (\a -> (\b -> f (a,b)))

uncurry'::(a->(a->a))->((a,a)->a)
uncurry' f = \(a,b) -> f a b

-- curry:
-- g (x,y) = x - y
-- ghci> curry g 2 3
-- -1

-- uncurry:
-- ghci> h x y = x - y
-- ghci> uncurry' h (2,3)
-- -1

