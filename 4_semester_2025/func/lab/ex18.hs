-- Napisz funkcję inits, która dla danej listy wyznaczy listę wszystkich jej odcinków
-- początkowych, np. inits [1,2,3,4] == [[],[1],[1,2],[1,2,3],[1,2,3,4]]

inits :: [a] -> [[a]]
inits [] = [[]]
inits (x:xs) = [] : map (x:) (inits xs)

-- [] : means "prepend an empty list to the list and map (x:) to the rest of the list"
-- (x:) means "prepend x to the list"
-- map (x:) means "prepend x to each list in the list"


initsh :: [a] -> [a] -> [[a]]
initsh xs [] = [reverse xs]
initsh xs (y: ys) = (reverse xs) : (initsh (y:xs) ys)
inits' xs = initsh [] xs 