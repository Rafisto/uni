fact3 n = case n of
          0 -> 1
          otheriwse -> n * fact3(n-1)