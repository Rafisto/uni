-- Oto jedna z możliwych implementacji funkcji partition:
-- partition : : (a => Bool) => [a] => ([a] , [a])
-- partition p xs = (filter p xs, filter ( not . p ) xs)

-- partition :: (a -> Bool) -> [a] -> ([a], [a])
-- partition p xs = (filter p xs, filter (not . p) xs)

-- example
-- partition even [1..10]

-- partition (>5) [1..10]

partition :: (a -> Bool) -> [a] -> ([a], [a])
partition p [] = ([], [])
partition p (x:xs) = if p x then (x:ys, zs) else (ys, x:zs)
  where (ys, zs) = partition p xs

-- p x (if passes) then add it to the left list, otherwise add it to the right list
-- where means "let" in Haskell