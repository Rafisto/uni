ghci> :t sum
sum :: (Foldable t, Num a) => t a -> a
ghci> :t product
product :: (Foldable t, Num a) => t a -> a
ghci> :t all
all :: Foldable t => (a -> Bool) -> t a -> Bool
ghci> :t any
any :: Foldable t => (a -> Bool) -> t a -> Bool

