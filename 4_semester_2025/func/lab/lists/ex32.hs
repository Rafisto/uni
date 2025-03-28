import Data.List

-- it works for intersect, not prefix
-- lprefix' :: Eq a => [[a]] -> [a]
-- lprefix' [] = []
-- lprefix' (x:xs) = foldl1 intersect (x:xs)

-- use transpose
prefix :: Eq a => [[a]] -> [a]
prefix [] = []
prefix (x:xs) = foldl1 intersect (x:xs)