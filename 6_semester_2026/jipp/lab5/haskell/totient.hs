module Totient (totient, totient2) where

import Data.List

import GCD
import Prime

totient :: Int -> Int
totient n
    | n <= 1 = n
    | otherwise = length [k | k <- [1..n], mgcd k n == 1]

-- better
totient2 :: Int -> Int
totient2 n
    | n <= 1 = 1
    -- | otherwise = foldl (*) 1 (s1 ++ s2) where
    -- | otherwise = foldl (*) (foldl (*) 1 s1) s2 where
    -- | otherwise = foldl (*) 1 $ fmap (foldl (*) 1) [s1, s2] where
    | otherwise = product $ fmap product [s1, s2] where 
        so = nub pf
        s1 = map (\x -> x - 1) so
        s2 = pf \\ so 
        pf = prime_factors n
