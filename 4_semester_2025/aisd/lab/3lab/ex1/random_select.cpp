#include <algorithm>
#include <iostream>
#include <vector>

#include "random_select.hpp"

using namespace std;

int main(void)
{
    size_t n;
    size_t kpos;
    vector<int> initial;

    size_t comparisons = 0;
    size_t swaps = 0;

    cin >> n;
    cin >> kpos;

    int temp;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> temp;
        initial.push_back(temp);
    }

    vector<int> arr = initial;
    int res = RandomSelect(arr, 0, n - 1, kpos, comparisons, swaps);

    if (n <= 30)
    {
        cout << "ultimate: ";
        for (size_t i = 0; i < n; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "initial: ";
        for (size_t i = 0; i < n; ++i)
        {
            cout << initial[i] << " ";
        }
        cout << endl;

        cout << kpos << "-select: " << res << endl;

        cout << "sorted: ";
        sort(initial.begin(), initial.end());
        for (size_t i = 0; i < initial.size(); ++i)
        {
            cout << initial[i] << " ";
        }
        cout << endl;
    }

    cout << "comparisons: " << comparisons << endl;
    cout << "swaps: " << swaps << endl;
}