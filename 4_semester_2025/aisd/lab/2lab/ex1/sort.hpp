#ifndef BASE_SORT_HPP
#define BASE_SORT_HPP

#include <vector>
#include <iostream>

using namespace std;

static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

template <class T>
vector<T> insertion_sort(int n, vector<T> A)
{
    int i;
    for (int j = 1; j < n; j++)
    {
        T key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
    return A;
}

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
vector<T> insertion_sort_with_logging(int n, vector<T> A)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    print_array(A);

    int i;
    for (int j = 1; j < n; j++)
    {
        T key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key)
        {
            comparisons++;
            A[i + 1] = A[i];
            swaps++;
            i = i - 1;
        }
        comparisons++;
        A[i + 1] = key;
    }

    cout << "Sorted array: ";
    print_array(A);

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    return A;
}

template <class T>
static int part_with_logging(vector<T> &A, int left, int right, int &comparisons, int &swaps)
{
    T pivot = A[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        comparisons++;
        if (A[j] <= pivot)
        {
            ++i;
            std::swap(A[i], A[j]);
            swaps++;
        }
    }
    std::swap(A[i + 1], A[right]);
    swaps++;
    return i + 1;
}

template <class T>
static void qs_with_logging(vector<T> &A, int left, int right, int &comparisons, int &swaps)
{
    if (left < right)
    {
        int pivotIndex = part_with_logging(A, left, right, comparisons, swaps);
        qs_with_logging(A, left, pivotIndex - 1, comparisons, swaps);
        qs_with_logging(A, pivotIndex + 1, right, comparisons, swaps);
    }
}

template <class T>
vector<T> quick_sort_with_logging(int n, vector<T> A)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    print_array(A);

    qs_with_logging(A, 0, n - 1, comparisons, swaps);

    cout << "Sorted array: ";
    print_array(A);

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    return A;
}

template <class T>
static int part(vector<T> &A, int left, int right)
{
    T pivot = A[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        if (A[j] <= pivot)
        {
            ++i;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[right]);
    return i + 1;
}

template <class T>
static void qs(vector<T> &A, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = part(A, left, right);
        qs(A, left, pivotIndex - 1);
        qs(A, pivotIndex + 1, right);
    }
}

template <class T>
vector<T> quick_sort(int n, vector<T> A)
{
    qs(A, 0, n - 1);
    return A;
}

template <class T>
static void hs_with_logging(vector<T> &arr, int left, int right, int threshold, int &comparisons, int &swaps)
{
    if (right - left + 1 <= threshold)
    {
        for (int i = left + 1; i <= right; ++i)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                comparisons++;
                arr[j + 1] = arr[j];
                swaps++;
                --j;
            }
            comparisons++;
            arr[j + 1] = key;
        }
    }
    else if (left < right)
    {
        int pivotIndex = part_with_logging(arr, left, right, comparisons, swaps);
        hs_with_logging(arr, left, pivotIndex - 1, threshold, comparisons, swaps);
        hs_with_logging(arr, pivotIndex + 1, right, threshold, comparisons, swaps);
    }
}

template <class T>
vector<T> hybrid_sort_with_logging(int n, vector<T> arr, int threshold = 5)
{
    int comparisons = 0;
    int swaps = 0;

    cout << "Initial array: ";
    print_array(arr);

    hs_with_logging(arr, 0, n - 1, threshold, comparisons, swaps);

    cout << "Sorted array: ";
    print_array(arr);

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

    return arr;
}

template <class T>
static void hs(vector<T> &arr, int left, int right, int threshold)
{
    if (right - left + 1 <= threshold)
    {
        for (int i = left + 1; i <= right; ++i)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }
    else if (left < right)
    {
        int pivotIndex = part(arr, left, right);
        hs(arr, left, pivotIndex - 1, threshold);
        hs(arr, pivotIndex + 1, right, threshold);
    }
}

template <class T>
vector<T> hybrid_sort(int n, vector<T> arr, int threshold = 5)
{
    hs(arr, 0, n - 1, threshold);
    return arr;
}

#endif // BASE_SORT_HPP