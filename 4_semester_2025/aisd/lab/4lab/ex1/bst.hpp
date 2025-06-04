#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;

typedef struct BSTNode
{
    BSTNode *left;
    BSTNode *right;
    int key;
    size_t height;
} BSTNode;

BSTNode *new_bst_node(int k);
BSTNode *bst_insert(BSTNode *node, int key);
BSTNode *bst_remove(BSTNode *node, int key);
size_t bst_height(BSTNode *node) { return node ? node->height : 0; }

inline BSTNode *new_bst_node(int k)
{
    BSTNode *node = new BSTNode;
    node->left = nullptr;
    node->right = nullptr;
    node->key = k;
    node->height = 1;
    return node;
}

inline void update_height(BSTNode *node)
{
    if (node)
        node->height = 1 + max(bst_height(node->left), bst_height(node->right));
}

inline BSTNode *bst_insert(BSTNode *node, int key)
{
    if (node == nullptr)
    {
        return new_bst_node(key);
    }

    if (key < node->key)
    {
        node->left = bst_insert(node->left, key);
    }
    else
    {
        node->right = bst_insert(node->right, key);
    }

    update_height(node);
    return node;
}

inline BSTNode *bst_remove(BSTNode *node, int key)
{
    if (node == nullptr)
        return node;

    if (key < node->key)
        return node;

    if (key < node->key)
    {
        node->left = bst_remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = bst_remove(node->right, key);
    }
    else
    {
        if (node->left == nullptr)
        {
            BSTNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            BSTNode *temp = node->left;
            delete node;
            return temp;
        }

        BSTNode *temp = node->right;
        while (temp && temp->left != nullptr)
        {
            temp = temp->left;
        }

        node->key = temp->key;
        node->right = bst_remove(node->right, temp->key);
    }

    update_height(node);
    return node;
}

vector<char> left_trace(100, ' ');
vector<char> right_trace(100, ' ');

inline void bst_print(const BSTNode *root, size_t depth = 1, char prefix = '-')
{
    if (root == nullptr)
        return;

    if (root->left != nullptr)
    {
        bst_print(root->left, depth + 1, '/');
    }

    if (prefix == '/')
        left_trace[depth - 1] = '|';
    if (prefix == '\\')
        right_trace[depth - 1] = ' ';

    if (depth == 0)
        cout << "-";
    if (depth > 0)
        cout << " ";
    for (size_t i = 0; i < depth - 1; i++)
    {
        if (left_trace[i] == '|' || right_trace[i] == '|')
        {
            cout << "| ";
        }
        else
        {
            cout << "  ";
        }
    }
    if (depth > 0)
        cout << prefix << "-";
    cout << "[" << root->key << "]" << endl;

    left_trace[depth] = ' ';
    if (root->right != nullptr)
    {
        right_trace[depth] = '|';
        bst_print(root->right, depth + 1, '\\');
    }
}

#endif // BST_HPP