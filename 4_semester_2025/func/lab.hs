select :: [Int] -> [Int]
select (x:y:xs)
    | x > y = x : select(y:xs)
    | otherwise = select(y:xs)
select _ = []

