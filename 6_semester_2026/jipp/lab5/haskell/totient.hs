module Totient where

import GCD

totient 0 = 0
totient 1 = 1
totient n = length [k | k <- [1..n], mgcd k n == 1]
