#include <iostream>
#include <vector>

#include "sort.hpp"

using namespace std;

int main()
{
    std::vector<int> numbers;
    int num;

    while (std::cin >> num)
    {
        numbers.push_back(num);
    }

    vector<int> result = insertion_sort_with_logging<int>(numbers.size(), numbers);

    for (const int &n : result)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}