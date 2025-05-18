#ifndef QUICK_SELECT_H
#define QUICK_SELECT_H

// https://en.wikipedia.org/wiki/Median_of_medians

#include <vector>
#include <algorithm>

#include "partition.hpp"

using namespace std;

int getMedian(vector<int> &arr, int left, int right, size_t &comparisons, size_t &swaps)
{
    comparisons += right - left + 1;
    swaps += right - left + 1;
    sort(arr.begin() + left, arr.begin() + right + 1);
    return arr[left + (right - left) / 2];
}

int QuickSelect(vector<int> &arr, int left, int right, int k, size_t &comparisons, size_t &swaps)
{
    if (left == right)
        return arr[left];

    vector<int> medians;
    for (int i = left; i <= right; i += 5)
    {
        int subRight = min(i + 4, right);
        int median = getMedian(arr, i, subRight, comparisons, swaps);
        medians.push_back(median);
    }

    int medianOfMedians;
    if (medians.size() == 1)
        medianOfMedians = medians[0];
    else
        medianOfMedians = QuickSelect(medians, 0, medians.size() - 1, medians.size() / 2, comparisons, swaps);

    int pivotIndex = LomutoPartition<int>(arr, left, right, medianOfMedians, comparisons, swaps);

    if (k == pivotIndex)
        return arr[pivotIndex];
    else if (k < pivotIndex)
        return QuickSelect(arr, left, pivotIndex - 1, k, comparisons, swaps);
    else
        return QuickSelect(arr, pivotIndex + 1, right, k, comparisons, swaps);
}

#endif // QUICK_SELECT_H