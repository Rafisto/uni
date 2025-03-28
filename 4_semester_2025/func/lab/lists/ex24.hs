zeros' n 
    | n < 5 = 0
    | otherwise = x + zeros' x
    where x = div n 5