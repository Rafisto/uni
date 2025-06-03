module Gray where

import Data.Bits (xor)

gray :: Int -> [Int]
gray 1 = [0, 1]
gray n
    | n < 1 = []
    | otherwise = map (\x -> x `xor` (x `div` 2)) [0 .. (2^n - 1)]

gray' :: Int -> [Int]
gray' n
    | n == 1 = [0,1]
    | otherwise = gray' (n - 1) ++ map (\x -> x + 2^(n - 1)) (reverse (gray' (n - 1)))

gray'' :: Int -> [[Char]]
gray'' n
    | n == 1 = ["0", "1"]
    | otherwise = map ('0':) (gray'' (n - 1)) ++ map ('1':) (reverse (gray'' (n - 1)))