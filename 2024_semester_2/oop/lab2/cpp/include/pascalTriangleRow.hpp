#ifndef PASCALTRIANGLEROW_HPP
#define PASCALTRIANGLEROW_HPP

#include <vector>
#include <stdexcept>

/**
 * @class PascalTriangleRow
 *
 * @brief This class generates and stores a vector of Pascal's triangle row elements given a row number and provides a method to get the n-th number.
 */
class PascalTriangleRow
{
private:
    /**
     * @brief Private vector of concurrent triangle row elements
     *
     * This vector stores all n-th row elements of Pascal's triangle.
     */
    std::vector<int> row;

public:
    /**
     * @brief Constructor for the PascalTriangleRow class
     *
     * @param n - any number greater or equal to 0
     */
    PascalTriangleRow(int n) noexcept(false);

    /**
     * @brief Get the m-th element of the defined row of Pascal's triangle
     *
     * @param m  - m-th element of the row unless m is more than the number of generated elements
     * @return std::vector<int>
     */
    int getCoefficient(int m) noexcept(false);
};

#endif