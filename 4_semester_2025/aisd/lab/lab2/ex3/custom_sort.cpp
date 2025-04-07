#include <iostream>
#include <vector>

#include "custom_sort.hpp"

using namespace std;

int main()
{
    vector<int> numbers;
    int num;

    while (cin >> num)
    {
        numbers.push_back(num);
    }

    int comparisons = 0, swaps = 0;
    customSort(numbers, comparisons, swaps);

    cout << "Total comparisons:  " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    for (const int &n : numbers)
    {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}