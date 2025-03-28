-- Przetestuj działanie funkcji foldl (+) 0 xs, foldr (+) 0 xs, foldl1 (+) xs,
-- foldr1 (+) xs oraz sum X na dużych listach liczb X.
-- Wskazówka: skorzystaj z polecenia GHCi :set +s; w celu usunięcia wyświetlania informacji skorzystaj
-- z polecenia :unset +s
-- Przetestuj następnie działanie funkcji foldl’ oraz foldr’ (znajdują się one w module Data.List).

-- ghci> foldr (+) 0 [1..10000000]
-- 50000005000000
-- (1.70 secs, 1,615,376,456 bytes)
-- ghci> foldl (+) 0 [1..10000000]
-- 50000005000000
-- (2.29 secs, 1,612,375,088 bytes)

-- ghci> foldl' (+) 0 [1..10000000]
-- 50000005000000
-- (0.24 secs, 880,074,800 bytes)

-- ghci> sum [1..1000000]
-- 500000500000
-- (0.04 secs, 88,073,256 bytes)

import Data.List

-- & = et (łac. i) - ligatura
-- fi - f łączy kropkę i