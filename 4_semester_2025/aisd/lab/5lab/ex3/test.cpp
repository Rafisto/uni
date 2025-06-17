#include <iostream>
#include <cassert>
#include <fstream>

#include "generator.hpp"
#include "binomialheap.hpp"

#define N 500

int main(int argc, char *argv[]) { 
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        return 1; 
    }

    std::cout << "Running tests with N = " << N << std::endl;
    std::cout << "Using file: " << filename << std::endl;

    std::vector<size_t> vcomparisons;

    std::vector<int> keys = generate_random_permutation(N);
    for (auto &key : keys) {
        key *= 2;
    }

    BinomialHeap *heap = make_binomial_heap();
    for (int i = 0; i < N; ++i) {
        size_t comparisons = 0;
        BHNode *node = new BHNode(keys[static_cast<size_t>(i)]);
        binomial_heap_insert(heap, node, comparisons);
        vcomparisons.push_back(comparisons);
    }

    std::vector<int> keys2 = generate_random_permutation(N);
    for (auto &key : keys2) {
        key = key * 2 + 1;
    }


    BinomialHeap *heap2 = make_binomial_heap();
    for (int i = 0; i < N; ++i) {
        size_t comparisons = 0;
        BHNode *node = new BHNode(keys2[static_cast<size_t>(i)]);
        binomial_heap_insert(heap2, node, comparisons);
        vcomparisons.push_back(comparisons);
    }


    size_t comparisons = 0;
    BinomialHeap *heap_union_result = binomial_heap_union(heap, heap2, comparisons);
    vcomparisons.push_back(comparisons);
    if (heap_union_result) {
        std::cout << "Heap union successful. New size: " << binomial_heap_size(heap_union_result) << std::endl;
    } else {
        std::cout << "Heap union failed." << std::endl;
        return 1;
    }

    std::vector<int> extracted_keys;
    for (size_t i = 0; i < 2 * N; ++i) {
        size_t comparisons = 0;
        BHNode *min_node = binomial_heap_extract_min(heap_union_result, comparisons);
        vcomparisons.push_back(comparisons);
        if (min_node) {
            extracted_keys.push_back(min_node->key);
            delete min_node;
        } else {
            std::cout << "Heap is empty." << std::endl;
            break;
        }
    }

    std::cout << "Extracted keys: ";
    for (const auto &key : extracted_keys) {
        std::cout << key << " ";
    }

    bool reverse_sorted = true;
    for (size_t i = 1; i < extracted_keys.size(); ++i) {
        if (extracted_keys[i - 1] > extracted_keys[i]) {
            std::cout << "Extracted keys are not in reverse order." << std::endl;
            std::cout << "Extracted keys: ";
            std::cout << extracted_keys[i - 1] << " " << extracted_keys[i] << std::endl;
            reverse_sorted = false;
            break;
        }
    }
    
    assert(reverse_sorted);
    std::cout << "All tests passed successfully!" << std::endl;

    for (size_t i = 0; i < vcomparisons.size(); ++i) {
        std::cout << i << ";" << vcomparisons[i] << " ";
    }
    std::cout << std::endl;
    
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (size_t i = 0; i < vcomparisons.size(); ++i) {
            if (i >= 0 && i < 500) {
                outfile << "keys1;";
            } else if (i >= 500 && i < 1000) {
                outfile << "keys2;";
            } else if (i == 1000) {
                outfile << "union;";
            } else {
                outfile << "emin;";
            }
            outfile << i << ";" << vcomparisons[i] << std::endl;
        }
        outfile.close();
    } else {
        std::cerr << "Failed to open test.txt for writing." << std::endl;
    }
}
