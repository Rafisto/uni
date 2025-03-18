-- Zadanie 19 — Napisz funkcję tails, która dla danej listy wyznaczy listę wszystkich jej odcinków
-- początkowych, np. tails [1,2,3,4] == [[],[4],[3,4],[2,3,4],[1,2,3,4]]

-- inits :: [a] -> [[a]]
-- inits [] = [[]]
-- inits (x:xs) = [] : map (x:) (inits xs)

-- tails :: [a] -> [[a]]
-- tails = map reverse . inits . reverse

tails :: [a] -> [[a]]
tails [] = [[]]
tails (xs:x) = (xs:x) : tails (tail (xs:x))

tails' :: [a] -> [[a]]
tails' xs = reverse (tails xs)