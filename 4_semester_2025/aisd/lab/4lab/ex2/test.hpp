#ifndef TEST_HPP
#define TEST_HPP

using namespace std;

#include <vector>
#include <iostream>
#include <cstddef>
#include <string>
#include <numeric>
#include <algorithm>

void print_csv_header() {
    cout << "testname,N,ds,"
    << "average_comparisons,max_comparisons,"
    << "average_pointer_operations,max_pointer_operations,"
    << "average_tree_height,max_tree_height,"
    << "average_cost,max_cost" << endl;
}

void print_test_summary(const string &testname,
                        size_t N, const string &ds,
                        const vector<unsigned long long> &comparisons,
                        const vector<unsigned long long> &pointer_operations,
                        const vector<size_t> &tree_heights,
                        const vector<unsigned long long> &costs)
{
    auto average = [](const auto &vec) -> unsigned long long
    {
        return vec.empty() ? 0 : accumulate(vec.begin(), vec.end(), 0ull) / vec.size();
    };

    cout << '"' << testname << '"' << ','
         << N << ','
         << '"' << ds << '"' << ','
         << average(comparisons) << ','
         << (comparisons.empty() ? 0 : *max_element(comparisons.begin(), comparisons.end())) << ','
         << average(pointer_operations) << ','
         << (pointer_operations.empty() ? 0 : *max_element(pointer_operations.begin(), pointer_operations.end())) << ','
         << average(tree_heights) << ','
         << (tree_heights.empty() ? 0 : *max_element(tree_heights.begin(), tree_heights.end())) << ','
         << average(costs) << ','
         << (costs.empty() ? 0 : *max_element(costs.begin(), costs.end()))
         << endl;
}

#endif // TEST_HPP