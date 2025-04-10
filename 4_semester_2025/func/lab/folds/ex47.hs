subsetlist :: [a] -> [a] -> Bool
subsetlist [] _ = True
subsetlist (x:xs) ys
    | elem x ys = subsetlist xs ys
    | otherwise = False