#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>
#include <iostream>

using namespace std;

template <class T>
void print_array(const vector<T> &arr)
{
    for (const auto &el : arr)
    {
        cout << (el < 10 ? "0" : "") << el << " ";
    }
    cout << endl;
}

template <class T>
void merge(vector<T> &arr, int left, int mid, int right, int &comparisons, int &swaps)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        comparisons++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        swaps++;
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        swaps++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

template <class T>
void merge_sort(vector<T> &arr, int left, int right, int &comparisons, int &swaps)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid, comparisons, swaps);
        merge_sort(arr, mid + 1, right, comparisons, swaps);

        merge(arr, left, mid, right, comparisons, swaps);
    }
}

template <class T>
vector<T> merge_sort_with_logging(vector<T> arr)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    print_array(arr);

    merge_sort(arr, 0, arr.size() - 1, comparisons, swaps);

    cout << "Sorted array: ";
    print_array(arr);

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    return arr;
}

#endif // MERGE_SORT_HPP