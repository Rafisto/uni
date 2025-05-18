#ifndef BASE_SORT_HPP
#define BASE_SORT_HPP

#include <vector>

using namespace std;

template <class T>
int select_kth(vector<T> &A, int left, int right, int k, size_t &comparisons, size_t &swaps)
{
    comparisons++;
    swaps++;
    if (left == right) return left;
    int pivotIndex = left + (right - left) / 2;
    T pivotValue = A[pivotIndex];
    swap(A[pivotIndex], A[right]);
    swaps++;
    int storeIndex = left;
    for (int i = left; i < right; ++i)
    {
        comparisons++;
        if (A[i] < pivotValue)
        {
            swaps++;
            swap(A[i], A[storeIndex]);
            storeIndex++;
        }
    }
    swaps++;
    swap(A[storeIndex], A[right]);
    if (k == storeIndex) return storeIndex;
    else if (k < storeIndex) return select_kth(A, left, storeIndex - 1, k, comparisons, swaps);
    else return select_kth(A, storeIndex + 1, right, k, comparisons, swaps);
}

template <class T>
static int part_with_select(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps) {
    int n = right - left + 1;
    int k = left + n/2;
    select_kth(A, left, right, k, comparisons, swaps);
    swap(A[k], A[right]);
    swaps++;
    
    T pivot = A[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        comparisons++;
        if (A[j] <= pivot) {
            ++i;
            swap(A[i], A[j]);
            swaps++;
        }
    }
    swap(A[i+1], A[right]);
    swaps++;
    return i+1;
}

template <class T>
static void qs_select(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps) {
    if (left < right) {
        int pivotIndex = part_with_select(A, left, right, comparisons, swaps);
        qs_select(A, left, pivotIndex-1, comparisons, swaps);
        qs_select(A, pivotIndex+1, right, comparisons, swaps);
    }
}

template <class T>
vector<T> quick_sort_select(int n, vector<T> A, size_t &comparisons, size_t &swaps) {
    qs_select(A, 0, n-1, comparisons, swaps);

    return A;
}

#endif // BASE_SORT_HPP