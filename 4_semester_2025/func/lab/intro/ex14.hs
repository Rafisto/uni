-- p(n) = perfect number (sum of divisors of n is n)

p :: Int -> Bool
p n = sum [k | k <- [1..n-1], n `mod` k == 0] == n

-- perfects :: Int -> [Int]

perfects :: Int -> [Int]
perfects n = [k | k <- [1..n], p k]