#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cstddef>

using namespace std;

typedef struct BSTNode
{
  BSTNode *left;
  BSTNode *right;
  int key;
  size_t height;
} BSTNode;

BSTNode *new_bst_node(int k);
BSTNode *bst_insert(BSTNode *node, int key, unsigned long long &comparisons, unsigned long long &pointer_operations);
BSTNode *bst_remove(BSTNode *node, int key, unsigned long long &comparisons, unsigned long long &pointer_operations);
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

inline BSTNode *bst_insert(BSTNode *node, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
  pointer_operations++;
  if (node == nullptr)
  {
    return new_bst_node(key);
  }

  comparisons++;
  if (key < node->key)
  {
    pointer_operations++;
    node->left = bst_insert(node->left, key, comparisons, pointer_operations);
  }
  else
  {
    pointer_operations++;
    node->right = bst_insert(node->right, key, comparisons, pointer_operations);
  }

  update_height(node);
  return node;
}

inline BSTNode *bst_remove(BSTNode *node, int key, unsigned long long &comparisons, unsigned long long &pointer_operations)
{
  pointer_operations++;
  if (node == nullptr)
    return node;

  comparisons++;
  if (key < node->key)
  {
    pointer_operations++;
    node->left = bst_remove(node->left, key, comparisons, pointer_operations);
  }
  else if (key > node->key)
  {
    comparisons++;
    pointer_operations++;
    node->right = bst_remove(node->right, key, comparisons, pointer_operations);
  }
  else
  {
    comparisons++;
    pointer_operations++;
    if (node->left == nullptr)
    {
      pointer_operations++;
      BSTNode *temp = node->right;
      delete node;
      return temp;
    }
    else if (node->right == nullptr)
    {
      pointer_operations++;
      BSTNode *temp = node->left;
      delete node;
      return temp;
    }

    BSTNode *temp = node->right;
    while (temp && temp->left != nullptr)
    {
      pointer_operations++;
      temp = temp->left;
    }

    pointer_operations++;
    node->key = temp->key;
    node->right = bst_remove(node->right, temp->key, comparisons, pointer_operations);
  }

  update_height(node);
  return node;
}

#endif // BST_HPP