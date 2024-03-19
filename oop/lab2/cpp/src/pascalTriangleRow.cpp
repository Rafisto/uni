#include <stdexcept>
#include <string>

#include <binomials.hpp>

#include <pascalTriangleRow.hpp>

PascalTriangleRow::PascalTriangleRow(const int n) noexcept(false)
{
    if (n < 0)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Invalid argument: " + std::to_string(n));
    }
    this->row = Binomials::generateRow(n);
}

int PascalTriangleRow::getCoefficient(int m) noexcept(false)
{
    if (m < 0)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "index must be greater or equal to 0. Got " + std::to_string(m) + " instead.");
    }
    if (static_cast<size_t>(m) >= this->row.size())
    {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "range exceeded. Index must be less than or equal to " + std::to_string(this->row.size() - 1) + ". Got " + std::to_string(m) + " instead.");
    }

    return this->row[static_cast<size_t>(m)];
}
