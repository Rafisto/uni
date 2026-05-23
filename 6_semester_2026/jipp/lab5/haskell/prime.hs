module Prime (prime_factors,primes) where

prime_factors :: Int -> [Int]
prime_factors n 
    | n <= 1 = []
    | otherwise = dv [] 2 n where
        dv acc c n
            | n == 1 = acc
            | n `mod` c == 0 = dv (c:acc) 2 (n `div` c)
            | otherwise = dv acc (c+1) n

primes :: Integral a => a -> [a]
primes n
    | n <= 1 = []
    | otherwise = eval [2..n] where
        eval [] = []
        eval (x:xs) = x : eval [i | i <- xs, i `mod` x /= 0]
