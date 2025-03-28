countEven :: [Int] -> Int
countEven xs = foldr (\x acc -> if even x then acc + 1 else acc) 0 xs
