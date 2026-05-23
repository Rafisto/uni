module Binomial where

-- binomial via rec. \binom{n}{k} = \binom{n-1}{k} + \binom{n-1}{k-1}
-- edge \binom{n}{0} = \binom{n}{n} = 1
-- edge \binom{n}{k} (k>n) = 0
binomial :: Int -> Int -> Int
binomial n 0 = 1
binomial n k
    | k > n = 0
    | k == n = 1
    | otherwise = binomial (n-1) k + binomial (n-1) (k-1)

pascalTriangleRow :: Int -> [Int]
pascalTriangleRow 0 = [1]
pascalTriangleRow 1 = [1, 1]
pascalTriangleRow n = zipWith (+) ((pascal (n-1)) ++ [0]) ([0] ++ (pascal (n-1)))

-- binomial2 via pascal, evaluate k-th element
-- should be way worse as it calculates full rows
binomial2 :: Int -> Int -> Int
binomial2 n 0 = 1
binomial2 n k
    | k > n = 0
    | k == n = 1
    | otherwise = (pascalTriangleRow n) !! k
