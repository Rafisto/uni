#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>
#include <sstream>

/**
 * @class BST
 * @brief Binary Search Tree implementation.
 *
 * This class represents a Binary Search Tree (BST) data structure.
 * It allows insertion, deletion, searching, and printing of elements.
 */
template <typename T>
class BST {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;

        Node(T value) : value(value), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void insertNode(Node* node, T value) const noexcept(true);
    Node* deleteNode(Node* node, T value) const noexcept(true);
    bool searchRecursive(const Node* node, T value) const noexcept(true);
    std::string printRecursive(const Node* node, int indent) const noexcept(true);
    void freeRecursive(Node * node) const noexcept(true);

public:
    BST() : root(nullptr) {}
    void insert(T value);
    void remove(T value);
    bool search(T value);
    std::string print();
    void freeTree();
};

/**
 * Inserts a new value into the binary search tree.
 *
 * @param value The value to be inserted.
 */
template <typename T>
void BST<T>::insert(T value)
{
    std::cout << "Inserting value: " << value << std::endl;
    if (root == nullptr)
    {
        std::cout << "Inserting root" << std::endl;
        root = new Node(value);
    }
    else
    {
        std::cout << "Inserting node" << std::endl;
        insertNode(root, value);
    }
}

/**
 * Removes a node with the specified value from the binary search tree.
 *
 * @param value The value to be removed from the binary search tree.
 */
template <typename T>
void BST<T>::remove(T value)
{
    root = deleteNode(root, value);
}

/**
 * Searches for a value in the binary search tree.
 *
 * @param value The value to search for.
 * @return True if the value is found, false otherwise.
 */
template <typename T>
bool BST<T>::search(T value)
{
    return searchRecursive(root, value);
}

/**
 * Prints the elements of the binary search tree in a specific order.
 *
 * @return A string representation of the binary search tree elements.
 */
template <typename T>
std::string BST<T>::print()
{
    return printRecursive(root, 0);
}

/**
 * Inserts a new node with the specified value into the binary search tree.
 *
 * @param node The root node of the binary search tree.
 * @param value The value to be inserted into the binary search tree.
 */
template <typename T>
void BST<T>::insertNode(Node *node, T value) const noexcept(true)
{
    if (value < node->value)
    {
        if (node->left == nullptr)
        {
            node->left = new Node(value);
            node->left->parent = node;
        }
        else
        {
            insertNode(node->left, value);
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            node->right = new Node(value);
            node->right->parent = node;
        }
        else
        {
            insertNode(node->right, value);
        }
    }
}

/**
 * @brief Deletes a node with the specified value from the binary search tree.
 * 
 * This function recursively searches for the node with the specified value in the binary search tree.
 * If the node is found, it is deleted from the tree and the tree is adjusted accordingly.
 * 
 * @param node A pointer to the root node of the binary search tree.
 * @param value The value to be deleted from the tree.
 * @return A pointer to the root node of the modified binary search tree.
 */
template <typename T>
typename BST<T>::Node *BST<T>::deleteNode(Node *node, T value) const noexcept(true)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value < node->value)
    {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            Node *temp = node;
            node = node->right;
            node->parent = temp->parent;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            Node *temp = node;
            node = node->left;
            node->parent = temp->parent;
            delete temp;
        }
        else
        {
            Node *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
    }

    return node;
}

/**
 * @brief Recursively searches for a value in the binary search tree.
 * 
 * @param node The current node being checked.
 * @param value The value to search for.
 * @return true if the value is found, false otherwise.
 */
template <typename T>
bool BST<T>::searchRecursive(const Node *node, T value) const noexcept(true)
{
    if (node == nullptr)
    {
        return false;
    }
    if (value < node->value)
    {
        return searchRecursive(node->left, value);
    }
    else if (value > node->value)
    {
        return searchRecursive(node->right, value);
    }
    else
    {
        return true;
    }
}

/**
 * Recursively prints the elements of the binary search tree starting from the given node.
 * 
 * @param node The starting node from which to print the elements.
 * @param indent The number of spaces to indent the output for each level of the tree.
 */
template <typename T>
std::string BST<T>::printRecursive(const Node *node, int indent) const noexcept(true)
{
    std::stringstream ss;
    
    if (node != nullptr)
    {
        ss << printRecursive(node->right, indent + 4);
        for (int i = 0; i < indent; i++)
        {
            ss << " ";
        }
        ss << node->value << "\n";
        ss << printRecursive(node->left, indent + 4);
    }

    return ss.str();
}

/**
 * @brief Frees the memory occupied by the binary search tree.
 * 
 * This function recursively frees the memory occupied by each node in the binary search tree.
 * It starts from the root node and traverses the tree in a post-order fashion.
 * 
 * @tparam T The type of elements stored in the binary search tree.
 */
template <typename T>
void BST<T>::freeTree() {
    freeRecursive(root);
}

/**
 * @brief Recursively frees the memory occupied by the nodes in the binary search tree.
 * 
 * This function is called recursively to free the memory occupied by each node in the binary search tree.
 * It starts from the given `node` and frees the memory for that node and its children nodes.
 * 
 * @param node A pointer to the node from which to start freeing the memory.
 */
template <typename T>
void BST<T>::freeRecursive(Node * node) const noexcept(true)
{
    if (node != nullptr) {
        freeRecursive(node->right);
        freeRecursive(node->left);
        delete node;
    }
}

#endif // BST_HPP