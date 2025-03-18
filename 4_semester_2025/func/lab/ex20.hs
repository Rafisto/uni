-- Zadanie 20 — Napisz funkcję splits, która dla danej listy xs wyznaczy listę wszystkich par (ys,zs)
-- takich, że xs == ys++zs.

splits :: Eq a => [a] -> [([a], [a])]
splits [] = [([], [])]
splits (x:xs) = ([], x:xs) : [(x:ys, zs) | (ys, zs) <- splits xs]