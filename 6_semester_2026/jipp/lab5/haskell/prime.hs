module Prime (prime_factors) where

prime_factors n 
    | n <= 1 = []
    | otherwise = dv [] 2 n where
        dv acc c n
            | n == 1 = acc
            | n `mod` c == 0 = dv ([c]++acc) 2 (n `div` c)
            | otherwise = dv acc (c+1) n
