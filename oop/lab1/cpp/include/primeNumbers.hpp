#ifndef PRIMENUMBERS_HPP
#define PRIMENUMBERS_HPP

#include <vector>
#include <stdexcept>

/**
 * @class PrimeNumbers
 *
 * @brief This class generates and stores a vector of prime numbers up to a given number and provides a method to get the n-th prime number.
 */
class PrimeNumbers
{
private:
    /**
     * @brief Private vector of concurrent prime numbers
     *
     * This vector stores all prime numbers up to a given number, provided in the constructor.
     */
    std::vector<int> primes;

public:
    /**
     * @brief Constructor for the PrimeNumbers class
     *
     * @param n - any number greater than 2
     */
    PrimeNumbers(int n) noexcept(false);

    /**
     * @brief Get the m-th prime number
     *
     * @param m - m-th prime number unless m is more than the number of generated primes
     * @return std::vector<int>
     */
    int getPrime(int m) noexcept(false);

    /**
     * @brief Get the count of generated prime numbers
     *
     * @return std::size_t
     */
    std::size_t getCount() const noexcept;
};

#endif