module Main where

import Binomial
import DiophantineEquation
import GCD
import MergeSort
import Prime
import Totient

main :: IO ()
main = do
    putStrLn $ "Binomial (5,2): " ++ show (binomial 5 2)
    putStrLn $ "Binomial2 (5,2): " ++ show (binomial2 5 2)
    putStrLn $ "Pascal Row 4: " ++ show (pascalTriangleRow 4)
    putStrLn $ "GCD of 48 and 18: " ++ show (mgcd 48 18)
    putStrLn $ "Diophantine (7, 3): " ++ show (de 7 3)
    let unsorted = [10, 3, 15, 7, 1, 9, 2]
    putStrLn $ "Sorted list: " ++ show (mergesort unsorted)
    putStrLn $ "Prime factors of 60: " ++ show (prime_factors 60)
    putStrLn $ "Primes up to 30: " ++ show (primes 30)
    putStrLn $ "Totient(1000): " ++ show (totient 1000)
    putStrLn $ "Totient2(1000): " ++ show (totient2 1000)