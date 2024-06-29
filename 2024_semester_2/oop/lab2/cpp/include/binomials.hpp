#ifndef BINOMIALS_HPP
#define BINOMIALS_HPP

#include <vector>
#include <stdexcept>

/**
 * @class Binomials
 *
 * @brief This static class contains useful methods for binomial coefficients
 *
 */
class Binomials
{
public:
    /**
     * @brief Constructor unavailable for a static class
     */
    Binomials() = delete;
    ~Binomials() = delete;

    /**
     * @brief Generates a vector of binomial coefficients for a given row of Pascal's triangle
     */
    static std::vector<int> generateRow(int n) noexcept(false);
};

#endif
