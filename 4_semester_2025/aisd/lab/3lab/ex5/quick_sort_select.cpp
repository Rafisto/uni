#include <iostream>
#include <vector>

#include "quick_sort_select.hpp"

using namespace std;

int main()
{
    vector<int> numbers;

    size_t comparisons = 0;
    size_t swaps = 0;

    int size = 0;

    cin >> size;

    for (int i = 0; i < size; ++i)
    {
        int n = 0;
        cin >> n;
        numbers.push_back(n);
    }

    vector<int> result = quick_sort_select<int>(numbers.size(), numbers, comparisons, swaps);

    if (size < 30)
    {
        for (const int &n : result)
        {
            cout << n << " ";
        }
        cout << endl;
    }

    cout << "comparisons: " << comparisons << endl;
    cout << "swaps: " << swaps << endl;

    return 0;
}