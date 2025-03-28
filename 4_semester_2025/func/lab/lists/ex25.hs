qs :: (Ord q) => [a] -> [a]
qs xs = quicksort xs []
    where
        quicksort [] acc = acc 
        quicksort (x:xs) acc = quicksort lesser(x:quicksort greater acc)
            where (lesser,greater) = partition(<=x) xs