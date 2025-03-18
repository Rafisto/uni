import Data.List (permutations)

isValid :: [Int] -> Bool
isValid perm = all safe [(i, perm !! i) | i <- [0 .. length perm - 1]]
    where safe (i, x) = all (\(j, y) -> abs (x - y) /= abs (i - j))
                          [(j, perm !! j) | j <- [0 .. length perm - 1], j /= i]

solveNGauss :: [[Int]]
solveNGauss = filter isValid (permutations [1..8])