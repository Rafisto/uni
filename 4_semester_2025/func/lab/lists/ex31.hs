-- takeWhile even [2,4,6,7,8,9] = [2,4,6]
takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' p (x:xs) = if p x then x : takeWhile' p xs else []

dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' p (x:xs) = if p x then dropWhile' p xs else x:xs