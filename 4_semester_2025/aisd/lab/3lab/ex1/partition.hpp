#ifndef PARTITION_H
#define PARTITION_H

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
size_t RandomPartition(vector<T> &arr, size_t p, size_t q, size_t &comparisons, size_t &swaps) {
    srand(time(0));
    size_t randomIndex = p + rand() % (q - p + 1);
    swaps++;
    swap(arr[randomIndex], arr[q]);
    T pivot = arr[q];
    size_t i = p - 1;
    for (size_t j = p; j < q; j++) 
    {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swaps++;
            swap(arr[i], arr[j]);
        }
    }
    swaps++;
    swap(arr[i + 1], arr[q]);
    return i + 1;
}

template <typename T>
size_t LomutoPartition(vector<T> &arr, size_t left, size_t right, T pivotValue, size_t &comparisons, size_t &swaps)
{
    size_t pivotIndex = left;
    while (pivotIndex <= right && arr[pivotIndex] != pivotValue) {
        pivotIndex++;
    }

    if (pivotIndex > right) pivotIndex = right;

    swaps++;
    swap(arr[pivotIndex], arr[right]);

    size_t i = left;
    for (size_t j = left; j < right; ++j)
    {
        comparisons++;
        if (arr[j] <= pivotValue)
        {
            swaps++;
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swaps++;
    swap(arr[i], arr[right]);
    return i;
}


#endif // PARTITION_H