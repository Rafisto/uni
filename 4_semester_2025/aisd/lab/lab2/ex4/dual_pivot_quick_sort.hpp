#ifndef DUAL_PIVOT_QUICK_SORT_HPP
#define DUAL_PIVOT_QUICK_SORT_HPP

#include <vector>
#include <iostream>

#include "utils.hpp"

using namespace std;

template <class T>
static void dual_pivot_partition_with_logging(vector<T> &A, int left, int right, int &lp, int &rp, int &comparisons, int &swaps)
{
    if (A[left] > A[right])
    {
        swaps++;
        std::swap(A[left], A[right]);
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
            std::swap(A[i], A[lt]);
            lt++;
        }
        else if (A[i] > pivot2)
        {
            comparisons++;
            swaps++;
            std::swap(A[i], A[gt]);
            gt--;
            i--;
        }
        i++;
    }

    lt--;
    gt++;

    std::swap(A[left], A[lt]);
    std::swap(A[right], A[gt]);
    swaps+=2;

    lp = lt;
    rp = gt;
}

template <class T>
static void dual_pivot_qs_with_logging(vector<T> &A, int left, int right, int &comparisons, int &swaps)
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
vector<T> dual_pivot_quick_sort_with_logging(int n, vector<T> A)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    print_array(A);

    dual_pivot_qs_with_logging(A, 0, n - 1, comparisons, swaps);

    cout << "Sorted array: ";
    print_array(A);

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    return A;
}

#endif // DUAL_PIVOT_QUICK_SORT_HPP
