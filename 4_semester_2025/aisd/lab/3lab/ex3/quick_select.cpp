#include <iostream>
#include <vector>

#include "quick_select.hpp"

using namespace std;

int main(const int argc, const char* argv[])
{
    if (argc != 2) {
        cout << "Usage : " << argv[0] << " <group_size>" << endl;
        exit(0);    
    }

    size_t group_size = atoi(argv[1]);

    if (group_size != 3 && group_size != 5 && group_size != 7 && group_size != 9) {
        cout << "group size must be 3, 5, 7 or 9" << endl;
        exit(1);
    }

    size_t n;
    size_t kpos;
    vector<int> initial;

    cin >> n;
    cin >> kpos;

    size_t comparisons = 0;
    size_t swaps = 0;

    int temp;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> temp;
        initial.push_back(temp);

    }

    vector<int> arr = initial;
    int res = QuickSelect(arr, 0, n - 1, kpos - 1, comparisons, swaps, group_size);

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