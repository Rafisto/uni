#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>

using namespace std;

template <class T>
void print_array(const std::vector<T> &arr)
{
    for (const auto &el : arr)
    {
        cout << (el < 10 ? "0" : "") << el << " ";
    }
    cout << endl;
}

#endif // UTILS_HPP