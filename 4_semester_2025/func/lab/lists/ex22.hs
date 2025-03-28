permutations :: [a] -> [[a]]
permutations [] = [[]]

permutations xs = [y: ys| (y,rest) <- selections xs, ys <- permutations rest]

selections :: [a] -> [(a, [a])]
selections [] = []
selections (x:xs) = (x,xs) : [(y, x:ys) | (y,ys) <- selections xs]
