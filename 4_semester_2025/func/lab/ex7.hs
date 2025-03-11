-- function examples
-- 1. (Int=>Int)=>Int
-- 2. (Int=>Int)=>(Int=>Int)
-- 3. (Int=>Int)=>(Int=>Int)=>(Int=>Int)

f1::(Int->Int)->Int
f1 f = f 0

f1test::(Int->Int)
f1test x = 4

f2::(Int->Int)->(Int->Int)
f2 f = \x -> f x 

f3::(Int->Int)->(Int->Int)->(Int->Int)
f3 f = \x -> \x -> f x
-- f3 f g = \x -> f x + g x

