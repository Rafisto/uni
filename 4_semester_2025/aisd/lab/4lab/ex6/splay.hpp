using namespace std;

#include <functional>
#include <iostream>

#ifndef SPLAY_HPP
#define SPLAY_HPP

typedef struct SplayNode
{
    SplayNode *left;
    SplayNode *right;
    SplayNode *parent;
    int key;
} SplayNode;

SplayNode *splay_new_node(int key);
void left_rotate(SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations);
void right_rotate(SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations);
void splay(SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations);
void replace(SplayNode *u, SplayNode *v, unsigned long long &comparisons, unsigned long long &pointer_operations);
SplayNode *subtree_minimum(SplayNode *u, unsigned long long &pointer_operations);
SplayNode *subtree_maximum(SplayNode *u, unsigned long long &pointer_operations);
void splay_insert(int key, SplayNode *&root, unsigned long long &comparisons, unsigned long long &pointer_operations);
void splay_remove(int key, SplayNode *&root, unsigned long long &comparisons, unsigned long long &pointer_operations);
size_t splay_height(SplayNode *root, unsigned long long &comparisons, unsigned long long &pointer_operations);

inline SplayNode *splay_new_node(int key)
{
    SplayNode *node = new SplayNode;
    node->key = key;
    node->left = node->right = node->parent = nullptr;
    return node;
}

inline void left_rotate(SplayNode *&root, SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    SplayNode *y = x->right;
    if (y)
    {
        x->right = y->left;
        ++pointer_operations;
        if (y->left)
        {
            y->left->parent = x;
            ++pointer_operations;
        }
        y->parent = x->parent;
        ++pointer_operations;
    }

    if (!x->parent)
    {
        root = y;
        ++pointer_operations;
    }
    else if (x == x->parent->left)
    {
        ++comparisons;
        x->parent->left = y;
        ++pointer_operations;
    }
    else
    {
        ++comparisons;
        x->parent->right = y;
        ++pointer_operations;
    }
    if (y)
    {
        y->left = x;
        ++pointer_operations;
    }
    x->parent = y;
    ++pointer_operations;
}

inline void right_rotate(SplayNode *&root, SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    SplayNode *y = x->left;
    if (y)
    {
        x->left = y->right;
        ++pointer_operations;
        if (y->right)
        {
            y->right->parent = x;
            ++pointer_operations;
        }
        y->parent = x->parent;
        ++pointer_operations;
    }

    if (!x->parent)
    {
        root = y;
        ++pointer_operations;
    }
    else if (x == x->parent->left)
    {
        ++comparisons;
        x->parent->left = y;
        ++pointer_operations;
    }
    else
    {
        ++comparisons;
        x->parent->right = y;
        ++pointer_operations;
    }
    if (y)
    {
        y->right = x;
        ++pointer_operations;
    }
    x->parent = y;
    ++pointer_operations;
}

inline void splay(SplayNode *&root, SplayNode *x, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    while (x->parent)
    {
        ++comparisons;
        if (!x->parent->parent)
        {
            ++comparisons;
            if (x->parent->left == x)
            {
                ++comparisons;
                right_rotate(root, x->parent, comparisons, pointer_operations);
            }
            else
            {
                left_rotate(root, x->parent, comparisons, pointer_operations);
            }
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent)
        {
            ++comparisons;
            ++comparisons;
            right_rotate(root, x->parent->parent, comparisons, pointer_operations);
            right_rotate(root, x->parent, comparisons, pointer_operations);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent)
        {
            ++comparisons;
            ++comparisons;
            left_rotate(root, x->parent->parent, comparisons, pointer_operations);
            left_rotate(root, x->parent, comparisons, pointer_operations);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent)
        {
            ++comparisons;
            ++comparisons;
            right_rotate(root, x->parent, comparisons, pointer_operations);
            left_rotate(root, x->parent, comparisons, pointer_operations);
        }
        else
        {
            ++comparisons;
            ++comparisons;
            left_rotate(root, x->parent, comparisons, pointer_operations);
            right_rotate(root, x->parent, comparisons, pointer_operations);
        }
    }
}

inline void replace(SplayNode *&root, SplayNode *u, SplayNode *v, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    if (!u->parent)
    {
        ++comparisons;
        root = v;
        ++pointer_operations;
    }
    else if (u == u->parent->left)
    {
        ++comparisons;
        u->parent->left = v;
        ++pointer_operations;
    }
    else
    {
        ++comparisons;
        u->parent->right = v;
        ++pointer_operations;
    }
    if (v)
    {
        ++comparisons;
        v->parent = u->parent;
        ++pointer_operations;
    }
}

inline SplayNode *subtree_minimum(SplayNode *u, unsigned long long &pointer_operations)
{
    while (u->left)
    {
        u = u->left;
        ++pointer_operations;
    }
    return u;
}

inline SplayNode *subtree_maximum(SplayNode *u, unsigned long long &pointer_operations)
{
    while (u->right)
    {
        u = u->right;
        ++pointer_operations;
    }
    return u;
}

inline SplayNode *splay_insert(SplayNode *&root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    SplayNode *z = root;
    SplayNode *p = nullptr;

    while (z)
    {
        p = z;
        ++pointer_operations;
        if (key > z->key)
        {
            ++comparisons;
            z = z->right;
            ++pointer_operations;
        }
        else
        {
            ++comparisons;
            z = z->left;
            ++pointer_operations;
        }
    }

    z = new SplayNode{nullptr, nullptr, p, key};
    ++pointer_operations;
    if (!p)
    {
        ++comparisons;
        root = z;
        ++pointer_operations;
    }
    else if (key > p->key)
    {
        ++comparisons;
        p->right = z;
        ++pointer_operations;
    }
    else
    {
        ++comparisons;
        p->left = z;
        ++pointer_operations;
    }

    splay(root, z, comparisons, pointer_operations);
    return z;
}

inline SplayNode *find(SplayNode *&root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    SplayNode *z = root;
    while (z)
    {
        ++comparisons;
        if (key > z->key)
        {
            z = z->right;
            ++pointer_operations;
        }
        else if (key < z->key)
        {
            z = z->left;
            ++pointer_operations;
        }
        else
        {
            splay(root, z, comparisons, pointer_operations);
            return z;
        }
    }
    return nullptr;
}

inline SplayNode *splay_remove(SplayNode *&root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    SplayNode *z = find(root, key, comparisons, pointer_operations);
    if (!z)
        return nullptr;

    splay(root, z, comparisons, pointer_operations);

    if (!z->left)
    {
        ++comparisons;
        replace(root, z, z->right, comparisons, pointer_operations);
    }
    else if (!z->right)
    {
        ++comparisons;
        replace(root, z, z->left, comparisons, pointer_operations);
    }
    else
    {
        SplayNode *y = subtree_minimum(z->right, pointer_operations);
        if (y->parent != z)
        {
            ++comparisons;
            replace(root, y, y->right, comparisons, pointer_operations);
            y->right = z->right;
            ++pointer_operations;
            y->right->parent = y;
            ++pointer_operations;
        }
        replace(root, z, y, comparisons, pointer_operations);
        y->left = z->left;
        ++pointer_operations;
        y->left->parent = y;
        ++pointer_operations;
    }

    delete z;
    ++pointer_operations;
    return root;
}

inline bool empty(SplayNode *root)
{
    return root == nullptr;
}

inline size_t splay_height(SplayNode *root)
{
    if (!root)
        return 0;

    size_t left_height = splay_height(root->left);
    size_t right_height = splay_height(root->right);
    return max(left_height, right_height) + 1;
}

vector<char> left_trace(100, ' ');
vector<char> right_trace(100, ' ');

inline void splay_print(const SplayNode *root, size_t depth = 1, char prefix = '-')
{
    if (root == nullptr)
        return;

    if (root->left != nullptr)
    {
        splay_print(root->left, depth + 1, '/');
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
        splay_print(root->right, depth + 1, '\\');
    }
}

#endif