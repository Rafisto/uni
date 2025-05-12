data T1 a b c = TT1 ( b => a , c => a )
data T2 a b c = TT2 ( Either b c ) => a

t21 (TT2 f) = TT1 (
    (\x -> f(Left x)),
    (\x -> f(Right x))
)

t12 (TT1 f) = TT2 (
    (\x -> case x of
        Left a -> f(Left a)
        Right b -> f(Right b))
)


|A^(B+C)|

b rozłączny z c

