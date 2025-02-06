## Rafal Wlodarczyk 2025 MPIS
import numpy as np

## PMF of X ~ Bin(n, p), n = {100, 1000, 10000}, p = 1/2

N = [100, 1000, 10000]
P = 1/2
E = lambda n: n * P
S = 1000 # Samples


## a) P(X >= 6/5 E[X])
for n in N:
    X = np.random.binomial(n, P, S)
    print(f"n = {n}, P(X >= 6/5 E[X]) = {np.mean(X >= 6/5 * E(n))}")
    
## b) P(|X - E[X]| <= 0.1 E[X])
for n in N:
    X = np.random.binomial(n, P, S)
    print(f"n = {n}, P(|X - E[X]| >= 0.1 E[X]) = {np.mean(np.abs(X - E(n)) >= 0.1 * E(n))}")
