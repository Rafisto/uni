module DiophantineEquation where

import GCD

-- solves ab + by = z = gcd(a,b)
de :: Int -> Int -> (Int, Int, Int)
de a 0 = (1, 0, a)
de 0 b = (0, 1, b)
de a b = (y, x - (a `div` b) * y, g)
  where (x, y, g) = de b (a `mod` b)
