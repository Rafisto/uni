#include <binomials.hpp>

#include <vector>
#include <string>

std::vector<int> Binomials::generateRow(int n) noexcept(false)
{
    if (n < 0)
    {
        throw std::invalid_argument("parameter n should be >= 0, got " + std::to_string(n));
    }

    std::vector<int> row;
    row.push_back(1);

    for (int i = 1; i <= n; i++)
    {
        row.push_back(static_cast<int>(static_cast<long long>(row[static_cast<std::vector<int>::size_type>(i) - 1]) * static_cast<long long>(n - i + 1) / static_cast<long long>(i)));
    }

    return row;
}