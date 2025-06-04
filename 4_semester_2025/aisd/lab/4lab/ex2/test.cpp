using namespace std;

#include <iostream>
#include <vector>
#include <string>

#include "bst.hpp"
#include "generator.hpp"
#include "test.hpp"

int test_insert_delete(vector<int> ikeys, vector<int> dkeys, size_t N, string testname, string ds)
{
    vector<unsigned long long> comparisons;
    vector<unsigned long long> pointer_operations;
    vector<size_t> tree_heights;
    vector<unsigned long long> costs;

    BSTNode *root = new_bst_node(ikeys[0]);

    unsigned long long local_comparisons = 0;
    unsigned long long local_pointer_operations = 0;

    for (size_t i = 1; i < N; ++i)
    {
        local_comparisons = 0;
        local_pointer_operations = 0;

        bst_insert(root, ikeys[i], local_comparisons, local_pointer_operations);

        tree_heights.push_back(bst_height(root));
        costs.push_back(local_comparisons + local_pointer_operations);
        comparisons.push_back(local_comparisons);
        pointer_operations.push_back(local_pointer_operations);
    }

    print_test_summary(testname+"_inserts", N, ds, comparisons, pointer_operations, tree_heights, costs);

    comparisons.clear();
    pointer_operations.clear();
    tree_heights.clear();
    costs.clear();

    for (size_t i = 0; i < N; ++i)
    {
        local_comparisons = 0;
        local_pointer_operations = 0;

        root = bst_remove(root, dkeys[i], local_comparisons, local_pointer_operations);

        tree_heights.push_back(bst_height(root));
        costs.push_back(local_comparisons + local_pointer_operations);
        comparisons.push_back(local_comparisons);
        pointer_operations.push_back(local_pointer_operations);
    }

    print_test_summary(testname+"_deletes", N, ds, comparisons, pointer_operations, tree_heights, costs);

    delete root;
    return 0;
}

int main(const int argc, const char *argv[])
{
    if (argc < 2) {
        print_csv_header();
        return 0;
    }

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " N " << endl;
        return 1;
    }

    size_t N = stoul(argv[1]);

    vector<int> ikeys_rand = generate_random_permutation(N);
    vector<int> dkeys_rand = generate_random_permutation(N);
    vector<int> ikeys_asc = ascending_keys(N);

    test_insert_delete(ikeys_rand, dkeys_rand, N, "random_keys_insertion_and_deletion", "BST");
    test_insert_delete(ikeys_asc, dkeys_rand, N, "ascending_keys_insertion_and_deletion", "BST");
}
