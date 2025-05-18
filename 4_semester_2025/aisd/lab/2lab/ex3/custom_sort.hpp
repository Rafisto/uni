#ifndef CUSTOM_SORT_HPP
#define CUSTOM_SORT_HPP

#include <vector>
#include <iostream>

using namespace std;

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

template <typename T>
void coalesce(vector<T> &arr, int &comparisons, int &swaps)
{
    int n = arr.size();
    if (n < 2)
        return;

    int start = 0;
    while (start < n)
    {
        int mid = start;
        while (mid + 1 < n && arr[mid] <= arr[mid + 1])
        {
            comparisons++;
            mid++;
        }

        int end = mid + 1;
        while (end + 1 < n && arr[end] <= arr[end + 1])
        {
            comparisons++;
            end++;
        }

        if (end < n)
        {
            merge(arr, start, mid, end, comparisons, swaps);
        }

        start = end + 1;
    }
}

template <typename T>
void customSort(vector<T> &arr, int &comparisons, int &swaps)
{
    while (true)
    {
        vector<T> prevArr = arr;
        coalesce(arr, comparisons, swaps);
        if (arr == prevArr)
        {
            break;
        }
    }
}

template <typename T>
void customSortWithLogging(vector<T> arr)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    for (const auto &el : arr)
    {
        cout << el << " ";
    }
    cout << endl;

    customSort(arr, comparisons, swaps);

    cout << "Sorted array: ";
    for (const auto &el : arr)
    {
        cout << el << " ";
    }
    cout << endl;

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;
}

#endif
