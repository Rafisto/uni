#ifndef BST_HPP
#define BST_HPP

using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstddef>

typedef struct RBTNode
{
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    int key;
    bool color;
} RBTNode;

RBTNode *rbt_new_node(int key, bool color = true);
RBTNode *rbt_insert(RBTNode *root, int key);
RBTNode *rbt_remove(RBTNode *root, int key);
size_t rbt_height(RBTNode *node);

inline RBTNode *rbt_new_node(int key, bool color)
{
    RBTNode *node = new RBTNode;
    node->key = key;
    node->color = color;
    node->left = node->right = node->parent = nullptr;
    return node;
}

inline size_t rbt_height(RBTNode *node)
{
    if (!node)
        return 0;
    size_t lh = node->left ? rbt_height(node->left) : 0;
    size_t rh = node->right ? rbt_height(node->right) : 0;
    return max(lh, rh) + 1;
}

inline void rbt_left_rotate(RBTNode *&root, RBTNode *x)
{
    RBTNode *y = x->right;

    x->right = y->left;

    if (y->left)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;

    x->parent = y;
}

inline void rbt_right_rotate(RBTNode *&root, RBTNode *y)
{
    RBTNode *x = y->left;

    y->left = x->right;

    if (x->right)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;

    y->parent = x;
}

inline void rbt_insert_fixup(RBTNode *&root, RBTNode *z)
{
    while (z->parent && z->parent->color)
    {
        RBTNode *gp = z->parent->parent;
        if (!gp)
            break;

        if (z->parent == gp->left)
        {
            RBTNode *y = gp->right;
            if (y && y->color)
            {
                z->parent->color = false;
                y->color = false;
                gp->color = true;
                z = gp;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rbt_left_rotate(root, z);
                }
                if (z->parent)
                    z->parent->color = false;
                if (gp)
                    gp->color = true;
                rbt_right_rotate(root, gp);
            }
        }
        else
        {
            RBTNode *y = gp->left;
            if (y && y->color)
            {
                z->parent->color = false;
                y->color = false;
                gp->color = true;
                z = gp;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbt_right_rotate(root, z);
                }
                if (z->parent)
                    z->parent->color = false;
                if (gp)
                    gp->color = true;
                rbt_left_rotate(root, gp);
            }
        }
    }
    if (root)
        root->color = false;
}

inline RBTNode *rbt_insert(RBTNode *root, int key)
{
    RBTNode *z = rbt_new_node(key, true);
    RBTNode *y = nullptr;
    RBTNode *x = root;
    while (x)
    {
        y = x;

        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if (!y)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    rbt_insert_fixup(root, z);
    return root;
}

inline RBTNode *rbt_minimum(RBTNode *node)
{
    while (node->left)
        node = node->left;
    return node;
}

inline void rbt_delete_fixup(RBTNode *&root, RBTNode *x, RBTNode *x_parent)
{
    while (x != root && (!x || !x->color))
    {
        if (x == x_parent->left)
        {
            RBTNode *w = x_parent->right;
            if (w && w->color)
            {
                w->color = false;
                x_parent->color = true;
                rbt_left_rotate(root, x_parent);
                w = x_parent->right;
            }
            if ((!w->left || !w->left->color) && (!w->right || !w->right->color))
            {
                w->color = true;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (!w->right || !w->right->color)
                {
                    if (w->left)
                        w->left->color = false;
                    w->color = true;
                    rbt_right_rotate(root, w);
                    w = x_parent->right;
                }
                w->color = x_parent->color;
                x_parent->color = false;
                if (w->right)
                    w->right->color = false;
                rbt_left_rotate(root, x_parent);
                x = root;
            }
        }
        else
        {
            RBTNode *w = x_parent->left;
            if (w && w->color)
            {
                w->color = false;
                x_parent->color = true;
                rbt_right_rotate(root, x_parent);
                w = x_parent->left;
            }
            if ((!w->right || !w->right->color) && (!w->left || !w->left->color))
            {
                w->color = true;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (!w->left || !w->left->color)
                {
                    if (w->right)
                        w->right->color = false;
                    w->color = true;
                    rbt_left_rotate(root, w);
                    w = x_parent->left;
                }
                w->color = x_parent->color;
                x_parent->color = false;
                if (w->left)
                    w->left->color = false;
                rbt_right_rotate(root, x_parent);
                x = root;
            }
        }
    }
    if (x)
        x->color = false;
}

inline void rbt_transplant(RBTNode *&root, RBTNode *u, RBTNode *v)
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

inline RBTNode *rbt_remove(RBTNode *root, int key)
{
    RBTNode *z = root;
    while (z)
    {

        if (key == z->key)
            break;
        else if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    if (!z)
        return root;
    RBTNode *y = z;
    bool y_original_color = y->color;
    RBTNode *x = nullptr;
    RBTNode *x_parent = nullptr;
    if (!z->left)
    {
        x = z->right;
        x_parent = z->parent;
        rbt_transplant(root, z, z->right);
    }
    else if (!z->right)
    {
        x = z->left;
        x_parent = z->parent;
        rbt_transplant(root, z, z->left);
    }
    else
    {
        y = rbt_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            if (x)
                x->parent = y;
            x_parent = y;
        }
        else
        {
            rbt_transplant(root, y, y->right);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
            x_parent = y->parent;
        }
        rbt_transplant(root, z, y);
        y->left = z->left;
        if (y->left)
            y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (!y_original_color)
        rbt_delete_fixup(root, x, x_parent);
    return root;
}

vector<char> left_trace(100, ' ');
vector<char> right_trace(100, ' ');

inline void rbt_print(const RBTNode *root, size_t depth = 1, char prefix = '-')
{
    if (root == nullptr)
        return;

    if (root->left != nullptr)
    {
        rbt_print(root->left, depth + 1, '/');
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

    if (root->color)
    {
        cout << "\033[31m";
        cout << "[R" << root->key << "]" << endl;
    }
    else
    {
        cout << "\033[30m";
        cout << "[B" << root->key << "]" << endl;
    }

    cout << "\033[0m";

    left_trace[depth] = ' ';
    if (root->right != nullptr)
    {
        right_trace[depth] = '|';
        rbt_print(root->right, depth + 1, '\\');
    }
}

#endif