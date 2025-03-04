#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void insertion_sort(vector<int> &arr)
{
    int length = arr.size();
    int key, i;
    for (int j = 1; j < length; j++)
    {
        key = arr[j];
        i = j - 1;
        while (i > -1 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i -= 1;
        }
        arr[i + 1] = key;
    }
}

void test_insertion_sort()
{
    vector<int> arr0 = {8, 2, 4, 9, 3, 6};
    vector<int> sorted_arr0 = {2, 3, 4, 6, 8, 9};
    insertion_sort(arr0);
    assert(arr0 == sorted_arr0);
    cout << "Test base case" << endl;

    vector<int> arr1 = {5, 2, 2, 2, 2, 3};
    vector<int> sorted_arr1 = {2, 2, 2, 2, 3, 5};
    insertion_sort(arr1);
    assert(arr1 == sorted_arr1);
    cout << "Test repeating elements" << endl;

    vector<int> arr2 = {0};
    vector<int> sorted_arr2 = {0};
    insertion_sort(arr2);
    assert(arr2 == sorted_arr2);
    cout << "Test single element" << endl;

    vector<int> arr3 = {};
    vector<int> sorted_arr3 = {};
    insertion_sort(arr3);
    assert(arr3 == sorted_arr3);
    cout << "Test empty vector" << endl;
}

int main()
{
    test_insertion_sort();
    return 0;
}