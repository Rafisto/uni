#ifndef RANDOM_SELECT_H
#define RANDOM_SELECT_H

#include <cstddef>
#include <cmath>
#include <vector>

#include "partition.hpp"

using namespace std;

template <typename T>
T RandomSelect(vector<T> &arr, size_t p, size_t q, size_t i, size_t &comparisons, size_t &swaps) {
    if (p == q) return arr[p];
    size_t r = RandomPartition(arr, p, q, comparisons, swaps);
    size_t k = r - p + 1;
    comparisons++;
    if (i == k) return arr[r];
    comparisons++;
    if (i < k) return RandomSelect(arr, p, r - 1, i, comparisons, swaps);
    else return RandomSelect(arr, r + 1, q, i - k, comparisons, swaps);
}


#endif // RANDOM_SELECT_H