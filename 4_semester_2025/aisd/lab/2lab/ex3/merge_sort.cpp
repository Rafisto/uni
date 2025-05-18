#include <iostream>
#include <vector>

#include "merge_sort.hpp"

using namespace std;

int main()
{
    vector<int> numbers;
    int num;

    while (cin >> num)
    {
        numbers.push_back(num);
    }

    vector<int> result = merge_sort_with_logging<int>(numbers);

    for (const int &n : result)
    {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}