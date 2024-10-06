#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <vector>
#include <stdexcept>

/**
 * @class Sieve
 *
 * @brief Sieve class is a static class containing only static prime generating method
 *
 */
class Sieve
{
public:
    /**
     * @brief Constructor unavailable for a static class
     */
    Sieve() = delete;
    ~Sieve() = delete;

    /**
     * @brief Generates a vector of prime numbers up to n
     *        Example: primes(10) -> {2, 3, 5, 7}
     *                 primes(20) -> {2, 3, 5, 7, 11, 13, 17, 19}
     *                 primes(1) -> {}
     *                 primes(0) -> {}
     *                 primes(-1) -> N/A (std::invalid_argument exception)
     *
     * @param n - any number
     *
     * @return vector of prime numbers up to n
     */
    static std::vector<int> Primes(int n) noexcept(false);
};

#endif
