#include <iostream>
#include <vector>

#include "sort.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <threshold>" << std::endl;
        return 1;
    }

    int threshold = std::stoi(argv[1]);
    std::vector<int> numbers;
    int num;

    while (std::cin >> num)
    {
        numbers.push_back(num);
    }

    vector<int> result = hybrid_sort_with_logging<int>(numbers.size(), numbers, threshold);

    for (const int &n : result)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}