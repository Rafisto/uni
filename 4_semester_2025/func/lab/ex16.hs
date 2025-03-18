-- dcp(n) = 1/n^2 * | (k,l) in {1...n} : gcd(k,l) = 1} |

dcp :: Int -> Double
dcp n = 1 / (fromIntegral n * fromIntegral n) * fromIntegral (length [(k, l) | k <- [1..n], l <- [1..n], gcd k l == 1])

-- hypothesis small_phi ~= 0.618
-- dcp n ~ small_phi = (1 - sqrt(5)) / 2

-- thought process
-- dcp(n) = 1/n^2 * | (k,l) in {1...n} : gcd(k,l) = 1} |
-- dcp(n) = dcp(n-1) + 2 *| k in {1...n} : gcd(k,n) = 1 |

dcpr :: Int -> Int
dcpr 1 = 1
dcpr n = dcpr (n-1) + 2 * length [k | k <- [1..n], gcd k n == 1]

dcpri :: Int -> Double
dcpri n = 1 / (fromIntegral n * fromIntegral n) * fromIntegral (dcpr n)

-- limit dcp 6/pi^2