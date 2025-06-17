#include <iostream>
#include <cassert>

#include "generator.hpp"
#include "binomialheap.hpp"


int main(int argc, char *argv[]) { 
    int N; 
    if (argc > 1) {
        N = std::atoi(argv[1]);
    } else {
        N = 500; 
    }

    std::cout << "Running tests with N = " << N << std::endl;

    std::vector<size_t> vcomparisons;

    std::vector<int> keys = generate_random_permutation(static_cast<size_t>(N));
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

    std::vector<int> keys2 = generate_random_permutation(static_cast<size_t>(N));
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
    for (size_t i = 0; i < 2 * static_cast<size_t>(N); ++i) {
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

    std::cout << "Total comparisons: " << std::accumulate(vcomparisons.begin(), vcomparisons.end(), 0) << std::endl;
}
