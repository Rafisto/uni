-- Napisz funkcje nub, która usunie z listy wszystkie duplikaty, np.
-- nub [1,1,2,2,2,1,4,1] == [1,2,4] 

nub :: [Int] -> [Int]
nub [] = []
nub (x:xs) = x : nub (filter (/= x) xs)

-- (/= x) means "not equal to x"