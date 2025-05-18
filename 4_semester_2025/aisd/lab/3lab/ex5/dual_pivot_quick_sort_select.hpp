#ifndef DUAL_PIVOT_QUICK_SORT_HPP
#define DUAL_PIVOT_QUICK_SORT_HPP

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
static void dual_pivot_partition_with_logging(vector<T> &A, int left, int right, int &lp, int &rp, size_t &comparisons, size_t &swaps)
{
    int n = right - left + 1;
    int mid1 = left + n / 3;
    int mid2 = left + 2 * n / 3;

    // Use Quickselect to find the two pivots
    select_kth(A, left, right, mid1, comparisons, swaps);
    select_kth(A, left, right, mid2, comparisons, swaps);

    swap(A[left], A[mid1]);
    swap(A[right], A[mid2]);
    swaps += 2;

    T pivot1 = A[left];
    T pivot2 = A[right];

    int i = left + 1;
    int lt = left + 1;
    int gt = right - 1;

    while (i <= gt)
    {
        comparisons++;
        if (A[i] < pivot1)
        {
            comparisons++;
            swaps++;
            swap(A[i], A[lt]);
            lt++;
        }
        else if (A[i] > pivot2)
        {
            comparisons++;
            swaps++;
            swap(A[i], A[gt]);
            gt--;
            i--;
        }
        i++;
    }

    lt--;
    gt++;

    swap(A[left], A[lt]);
    swap(A[right], A[gt]);
    swaps += 2;

    lp = lt;
    rp = gt;
}

template <class T>
static void dual_pivot_qs_with_logging(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps)
{
    comparisons++;
    if (left < right)
    {
        int lp, rp;
        dual_pivot_partition_with_logging(A, left, right, lp, rp, comparisons, swaps);

        dual_pivot_qs_with_logging(A, left, lp - 1, comparisons, swaps);
        dual_pivot_qs_with_logging(A, lp + 1, rp - 1, comparisons, swaps);
        dual_pivot_qs_with_logging(A, rp + 1, right, comparisons, swaps);
    }
}

template <class T>
vector<T> dual_pivot_quick_sort_with_logging(int n, vector<T> A, size_t &comparisons, size_t &swaps)
{
    dual_pivot_qs_with_logging(A, 0, n - 1, comparisons, swaps);

    return A;
}

#endif // DUAL_PIVOT_QUICK_SORT_HPP
