#ifndef BST_HPP
#define BST_HPP

using namespace std;

#include <algorithm>
#include <cstddef>

typedef struct RBTNode
{
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    size_t height;
    int key;
    bool color;
} RBTNode;

RBTNode *rbt_new_node(int key, bool color = true);
RBTNode *rbt_insert(RBTNode *root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations);
RBTNode *rbt_remove(RBTNode *root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations);
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

inline void rbt_left_rotate(RBTNode *&root, RBTNode *x, unsigned long long &pointer_operations)
{
    RBTNode *y = x->right;
    pointer_operations++;
    x->right = y->left;
    pointer_operations++;
    if (y->left)
    {
        y->left->parent = x;
        pointer_operations++;
    }
    y->parent = x->parent;
    pointer_operations++;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    pointer_operations++;
    y->left = x;
    pointer_operations++;
    x->parent = y;
    pointer_operations++;
}

inline void rbt_right_rotate(RBTNode *&root, RBTNode *y, unsigned long long &pointer_operations)
{
    RBTNode *x = y->left;
    pointer_operations++;
    y->left = x->right;
    pointer_operations++;
    if (x->right)
    {
        x->right->parent = y;
        pointer_operations++;
    }
    x->parent = y->parent;
    pointer_operations++;
    if (!y->parent)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    pointer_operations++;
    x->right = y;
    pointer_operations++;
    y->parent = x;
    pointer_operations++;
}

inline void rbt_insert_fixup(RBTNode *&root, RBTNode *z, unsigned long long &pointer_operations)
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
                    rbt_left_rotate(root, z, pointer_operations);
                }
                if (z->parent)
                    z->parent->color = false;
                if (gp)
                    gp->color = true;
                rbt_right_rotate(root, gp, pointer_operations);
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
                    rbt_right_rotate(root, z, pointer_operations);
                }
                if (z->parent)
                    z->parent->color = false;
                if (gp)
                    gp->color = true;
                rbt_left_rotate(root, gp, pointer_operations);
            }
        }
    }
    if (root)
        root->color = false;
}

inline RBTNode *rbt_insert(RBTNode *root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    RBTNode *z = rbt_new_node(key, true);
    RBTNode *y = nullptr;
    RBTNode *x = root;
    while (x)
    {
        y = x;
        comparisons++;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
        pointer_operations++;
    }
    z->parent = y;
    pointer_operations++;
    if (!y)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    pointer_operations++;
    rbt_insert_fixup(root, z, pointer_operations);
    return root;
}

inline RBTNode *rbt_minimum(RBTNode *node)
{
    while (node->left)
        node = node->left;
    return node;
}

inline void rbt_delete_fixup(RBTNode *&root, RBTNode *x, RBTNode *x_parent, unsigned long long &pointer_operations)
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
                rbt_left_rotate(root, x_parent, pointer_operations);
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
                    rbt_right_rotate(root, w, pointer_operations);
                    w = x_parent->right;
                }
                w->color = x_parent->color;
                x_parent->color = false;
                if (w->right)
                    w->right->color = false;
                rbt_left_rotate(root, x_parent, pointer_operations);
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
                rbt_right_rotate(root, x_parent, pointer_operations);
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
                    rbt_left_rotate(root, w, pointer_operations);
                    w = x_parent->left;
                }
                w->color = x_parent->color;
                x_parent->color = false;
                if (w->left)
                    w->left->color = false;
                rbt_right_rotate(root, x_parent, pointer_operations);
                x = root;
            }
        }
    }
    if (x)
        x->color = false;
}

inline void rbt_transplant(RBTNode *&root, RBTNode *u, RBTNode *v, unsigned long long &pointer_operations)
{
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    pointer_operations++;
    if (v)
        v->parent = u->parent;
    pointer_operations++;
}

inline RBTNode *rbt_remove(RBTNode *root, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
    RBTNode *z = root;
    while (z)
    {
        comparisons++;
        if (key == z->key)
            break;
        else if (key < z->key)
            z = z->left;
        else
            z = z->right;
        pointer_operations++;
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
        rbt_transplant(root, z, z->right, pointer_operations);
    }
    else if (!z->right)
    {
        x = z->left;
        x_parent = z->parent;
        rbt_transplant(root, z, z->left, pointer_operations);
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
            rbt_transplant(root, y, y->right, pointer_operations);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
            x_parent = y->parent;
        }
        rbt_transplant(root, z, y, pointer_operations);
        y->left = z->left;
        if (y->left)
            y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (!y_original_color)
        rbt_delete_fixup(root, x, x_parent, pointer_operations);
    return root;
}

#endif