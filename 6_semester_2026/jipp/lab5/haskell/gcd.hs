module GCD (mgcd) where

mgcd :: Int -> Int -> Int
mgcd a 0 = a
mgcd 0 b = b
mgcd a b 
    | b == 1 = a
    | a > b = gcd b (a `mod` b)
    | b > a = gcd a (b `mod` a)
    | a == b = a