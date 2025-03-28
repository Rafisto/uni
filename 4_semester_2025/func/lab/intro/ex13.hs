-- φ(n) = card({k <= n : gcd(k, n) = 1})

φ :: Int -> Int
φ n = length [k | k <- [1..n], gcd k n == 1]

-- sum k|n phi(n) = n

-- sum k|n phi(n) * I(n/k)

-- phi * I splot dirichleta