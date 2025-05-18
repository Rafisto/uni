#ifndef DUAL_PIVOT_QUICK_SORT_HPP
#define DUAL_PIVOT_QUICK_SORT_HPP

#include <vector>

using namespace std;

template <class T>
static void dual_pivot_part(vector<T> &A, int left, int right, int &lp, int &rp, size_t &comparisons, size_t &swaps)
{
    if (A[left] > A[right])
    {
        swaps++;
        swap(A[left], A[right]);
    }
    comparisons++;

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
    swaps+=2;

    lp = lt;
    rp = gt;
}

template <class T>
static void dual_pivot_qs(vector<T> &A, int left, int right, size_t &comparisons, size_t &swaps)
{
    comparisons++;
    if (left < right)
    {
        int lp, rp;
        dual_pivot_part(A, left, right, lp, rp, comparisons, swaps);

        dual_pivot_qs(A, left, lp - 1, comparisons, swaps);
        dual_pivot_qs(A, lp + 1, rp - 1, comparisons, swaps);
        dual_pivot_qs(A, rp + 1, right, comparisons, swaps);
    }
}

template <class T>
vector<T> dual_pivot_quick_sort(int n, vector<T> A, size_t &comparisons, size_t &swaps)
{
    dual_pivot_qs(A, 0, n - 1, comparisons, swaps);

    return A;
}

#endif // DUAL_PIVOT_QUICK_SORT_HPP
