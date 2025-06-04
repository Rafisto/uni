using namespace std;

#include <iostream>
#include <vector>

#include "bst.hpp"
#include "generator.hpp"

#define N 30

int test_insert_delete(vector<int> ikeys, vector<int> dkeys)
{
    cout << "Insertion keys: ";
    for (int key : ikeys)
        cout << key << " ";

    cout << "\nDeletion keys: ";

    for (int key : dkeys)
        cout << key << " ";

    cout << endl;

    cout << "insert " << ikeys[0] << endl;
    BSTNode *root = new_bst_node(ikeys[0]);
    bst_print(root);
    cout << endl;

    for (size_t i = 1; i < N; ++i)
    {
        cout << "height " << bst_height(root) << endl;
        cout << "insert " << ikeys[i] << endl;
        bst_insert(root, ikeys[i]);
        bst_print(root);
        cout << endl;
    }

    for (size_t i = 0; i < N; ++i)
    {
        cout << "delete " << dkeys[i] << endl;
        root = bst_remove(root, dkeys[i]);
        bst_print(root);
        cout << endl;
    }

    delete root;
    return 0;
}

int main(void)
{
    vector<int> ikeys_rand = generate_random_permutation(N);
    vector<int> dkeys_rand = generate_random_permutation(N);
    vector<int> ikeys_asc = ascending_keys(N);

    cout << "Random keys insertion and deletion:" << endl;
    test_insert_delete(ikeys_rand, dkeys_rand);

    cout << "Ascending keys insertion and deletion:" << endl;
    test_insert_delete(ikeys_asc, dkeys_rand);
}
