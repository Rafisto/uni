-- import Distribution.Simple.Utils (xargs)
-- take 10 [1..]

-- l2 = 2:l2

-- l2 !! 0 -- 0

-- l2 !! 1 = (2:l2) !! 1 = l2 !! 0 = 2
-- it is not a good code

-- "infinite" array is just a formula a next element
-- c++ 2020 coroutines / yield

-- repeat' x = xs where xs = x : xs

-- iterate' :: (a  -> a) -> a -> [a]
-- iterate' f x = x : iterafe f (f x)

-- [x, f x, ff x, fff x, ffff x, ...]

-- sqrt(a) 
-- x_0 = 0
-- x_{n+1} = 1/2 * (x_n + a/x_n)
-- następny krok zwiększa dwukrotnie

-- approSqrt :: Double -> [Double]
-- approSqrt a = iterate (\x -> (x+ a/x)/2) a

-- liczby Fibonacciego

-- f 0 = 0
-- f 1 = 1
-- f n = f (n-1) + f (n-2)

-- fib = 0:1:f2:f3:f4:...
-- fib = 0:1:f0+f1:f1+f2:f2+f3
-- fib = 0:1:fib
-- fib = 0:1:(fib + tail (fib))

fib = 0:1: zipWith (-) fib (tail fib)

sieve (p:xs) = p : sieve (filter (\n -> mod n p /= 0) xs)
primes = sieve [2..]

bsieve (p:xs) = p: sieve (filter(\n -> n<p*p || (mod n p /=0)) xs) 
bprimes = sieve[2..]

addGF xs ys = zipWith (+) xs ys
-- take 10 addGF (repeat 3) (repeat 5)

