#ifndef BASE_SORT_HPP
#define BASE_SORT_HPP

#include <vector>

using namespace std;

template <class T>
static int part(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps)
{
    T pivot = A[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        comparisons++;
        if (A[j] <= pivot)
        {
            ++i;
            swap(A[i], A[j]);
            swaps++;
        }
    }
    swap(A[i + 1], A[right]);
    swaps++;
    return i + 1;
}

template <class T>
static void qs(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps)
{
    if (left < right)
    {
        int pivotIndex = part(A, left, right, comparisons, swaps);
        qs(A, left, pivotIndex - 1, comparisons, swaps);
        qs(A, pivotIndex + 1, right, comparisons, swaps);
    }
}

template <class T>
vector<T> quick_sort(int n, vector<T> A, size_t &comparisons, size_t &swaps)
{
    qs(A, 0, n - 1, comparisons, swaps);
    return A;
}

#endif // BASE_SORT_HPP