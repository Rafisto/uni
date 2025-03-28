-- bubbleSort :: Ord a => [a] -> [a]
-- bubbleSort [] = []
-- bubbleSort [x] = [x]
-- bubbleSort (x:y:xs) = if x > y then y : bubbleSort (x:xs) else x : bubbleSort (y:xs)

-- isSorted :: (Ord a) => [a] -> Bool
-- isSorted [] = True
-- isSorted [x] = True
-- isSorted (x:y:xs) = x <= y && isSorted (y:xs)

-- defnitelySort :: Ord a => [a] -> [a]
-- defnitelySort xs = if isSorted xs then xs else defnitelySort (bubbleSort xs)

bub :: Ord a => [a] -> [a]
bub [] = []
bub [x] = [x]
bub (x:y:xs)
    | x <= y = x : bub (y:xs)
    | otherwise = bub (y : bub (x:xs))