rev [] = []
rev (x:xd) = rev xd ++[x]
-- f(n) = f(n-1) + O(n)
-- f(n) <= k*(n) + k*(n-1) + ... + k = k * (n(n+1)) ~ O(n^2)