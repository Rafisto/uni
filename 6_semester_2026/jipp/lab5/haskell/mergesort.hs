module MergeSort where

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys 
merge (x:xs) (y:ys)
    | x < y = x : merge xs (y:ys)
    | otherwise = y : merge (x:xs) ys

mergesort :: Ord a => [a] -> [a]
mergesort [] = []
mergesort [x] = [x]
mergesort (x:xs) = merge (take l (x:xs)) (drop l (x:xs))
    where l = length (x:xs) `div` 2

-- mergesort [1,3,5,7,9,2,4,6,8,10]
