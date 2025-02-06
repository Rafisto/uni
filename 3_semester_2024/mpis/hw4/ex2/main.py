# Rafal Wlodarczyk 28-01-2025
import numpy as np

## Model
## S_{N} = \sum_{n=1}^{N} X_{n}, where X_{n}, 1 <= n <= N, are i.i.d. random variables.
## X_{n} = 1 or -1 both with probability p = 1/2
## For N=0 assume S_{0} = 0

## a) calculate all CDF functions for N \in \{5, 10, 15, 20, 25, 30 \}
for N in [5, 10, 15, 20, 25, 30]:
    