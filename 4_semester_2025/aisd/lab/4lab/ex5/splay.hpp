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
void left_rotate(SplayNode *x);
void right_rotate(SplayNode *x);
void splay(SplayNode *x);
void replace(SplayNode *u, SplayNode *v);
SplayNode *subtree_minimum(SplayNode *u);
SplayNode *subtree_maximum(SplayNode *u);
void splay_insert(int key);

inline SplayNode *splay_new_node(int key)
{
    SplayNode *node = new SplayNode;
    node->key = key;
    node->left = node->right = node->parent = nullptr;
    return node;
}

inline void left_rotate(SplayNode *&root, SplayNode *x)
{
    SplayNode *y = x->right;
    if (y)
    {
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
    }

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    if (y)
        y->left = x;
    x->parent = y;
}

inline void right_rotate(SplayNode *&root, SplayNode *x)
{
    SplayNode *y = x->left;
    if (y)
    {
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->parent = x->parent;
    }
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    if (y)
        y->right = x;
    x->parent = y;
}

inline void splay(SplayNode *&root, SplayNode *x)
{
    while (x->parent)
    {
        if (!x->parent->parent)
        {
            if (x->parent->left == x)
                right_rotate(root, x->parent);
            else
                left_rotate(root, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent)
        {
            right_rotate(root, x->parent->parent);
            right_rotate(root, x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent)
        {
            left_rotate(root, x->parent->parent);
            left_rotate(root, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent)
        {
            right_rotate(root, x->parent);
            left_rotate(root, x->parent);
        }
        else
        {
            left_rotate(root, x->parent);
            right_rotate(root, x->parent);
        }
    }
}

inline void replace(SplayNode *&root, SplayNode *u, SplayNode *v)
{
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

inline SplayNode *subtree_minimum(SplayNode *u)
{
    while (u->left)
        u = u->left;
    return u;
}

inline SplayNode *subtree_maximum(SplayNode *u)
{
    while (u->right)
        u = u->right;
    return u;
}

inline void splay_insert(SplayNode *&root, int key)
{
    SplayNode *z = root;
    SplayNode *p = nullptr;

    while (z)
    {
        p = z;
        if (key > z->key)
            z = z->right;
        else
            z = z->left;
    }

    z = new SplayNode{nullptr, nullptr, p, key};
    if (!p)
        root = z;
    else if (key > p->key)
        p->right = z;
    else
        p->left = z;

    splay(root, z);
}

inline SplayNode *find(SplayNode *&root, int key)
{
    SplayNode *z = root;
    while (z)
    {
        if (key > z->key)
            z = z->right;
        else if (key < z->key)
            z = z->left;
        else
        {
            splay(root, z);
            return z;
        }
    }
    return nullptr;
}

inline void splay_remove(SplayNode *&root, int key)
{
    SplayNode *z = find(root, key);
    if (!z)
        return;

    splay(root, z);

    if (!z->left)
        replace(root, z, z->right);
    else if (!z->right)
        replace(root, z, z->left);
    else
    {
        SplayNode *y = subtree_minimum(z->right);
        if (y->parent != z)
        {
            replace(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        replace(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    delete z;
}

inline int minimum(SplayNode *root)
{
    return subtree_minimum(root)->key;
}

inline int maximum(SplayNode *root)
{
    return subtree_maximum(root)->key;
}

inline bool empty(SplayNode *root)
{
    return root == nullptr;
}

inline size_t height(SplayNode *root)
{
    if (!root)
        return 0;
    size_t left_height = height(root->left);
    size_t right_height = height(root->right);
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

#endif // SPLAY_HPP