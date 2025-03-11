{- 
    file = W2.hs
    author = JCI
    date = 11.03.2025
-}

-- prelude = Haskell Standard Library
-- :r reload last file

module W2 where

id' x = x

-- div n 2
-- n `div` 2 (infix)

coll n
    | n == 1 = 1
    | even n = coll (div n 2)
    | otherwise = coll (3 * n + 1)


collatz :: (Int, Int) -> (Int, Int)
collatz (n, s) | n == 1 = (n, s)
               | even n = collatz (div n 2, s + 1)
               | otherwise = collatz (3 * n + 1, s + 1)

-- snd - second element of a tuple
lez n = snd(collatz (n,0))