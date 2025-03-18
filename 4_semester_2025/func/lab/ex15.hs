-- friends (m,n) return if sum of divisors of m is n and sum of divisors of n is m

friends :: (Int, Int) -> Bool
friends (m, n) = sum [k | k <- [1..m-1], m `mod` k == 0] == n && sum [k | k <- [1..n-1], n `mod` k == 0] == m && m /= n

-- friends (220, 284)
-- friendlist
friendlist :: Int -> [(Int, Int)]
friendlist n = [(m, n) | m <- [1..n], n <- [1..n], friends (m, n)]