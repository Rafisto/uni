map'::(a->b)->[a]->[b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs

-- map'(\x -> x^2)[1..10]

zip'::([a],[b])->[(a,b)]
zip' ([], _) = []
zip' (_, []) = []
zip' (x:xs, y:ys) = (x, y) : zip' (xs, ys)

-- zip'([1,2,3], [4,5,6])

zipWith'::(a->b->c)->([a],[b])->[c]
zipWith' _ ([], _) = []
zipWith' _ (_, []) = []
zipWith' f (x:xs, y:ys) = f x y : zipWith' f (xs, ys)

-- zipWith'(\x y -> x + y)([1,2,3], [4,5,6])

filter' _ [] = []
filter' p (x:xs) = if p x then x:filter' p xs
                   else filter' p xs

-- filter'(\x -> x `mod` 2 == 0)[1..10]

take'::Int->[a]->[a]
take' 0 _ = []
take' _ [] = []
take' n (x:xs) = x : take' (n-1) xs

-- take' 3 [1..10]

drop'::Int->[a]->[a]
drop' 0 xs = xs
drop' _ [] = []
drop' n (x:xs) = drop' (n-1) xs

-- drop' 3 [1..10]