#include <iostream>
#include <string>
#include <sstream>

#include <bst.hpp>
#include <stringConverter.hpp>

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

template <typename T>
void BST<T>::remove(T value)
{
    root = deleteNode(root, value);
}

template <typename T>
bool BST<T>::search(T value)
{
    return searchRecursive(root, value);
}

template <typename T>
std::string BST<T>::print()
{
    return printRecursive(root, 0);
}

template <typename T>
void BST<T>::insertNode(Node *node, T value)
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

template <typename T>
typename BST<T>::Node *BST<T>::deleteNode(Node *node, T value)
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

template <typename T>
bool BST<T>::searchRecursive(Node *node, T value)
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

template <typename T>
std::string BST<T>::printRecursive(Node *node, int indent)
{
    std::stringstream ss;
    
    if (node != nullptr)
    {
        ss << printRecursive(node->right, indent + 4);
        for (int i = 0; i < indent; i++)
        {
            ss << " ";
        }
        ss << StringConverter::valToString<T>(node->value) << "\n";
        ss << printRecursive(node->left, indent + 4);
    }

    return ss.str();
}

template void BST<int>::insert(int);
template void BST<int>::remove(int);
template bool BST<int>::search(int);
template std::string BST<int>::print();
template void BST<std::string>::insert(std::string);
template void BST<std::string>::remove(std::string);
template bool BST<std::string>::search(std::string);
template std::string BST<std::string>::print();
template void BST<double>::insert(double);
template void BST<double>::remove(double);
template bool BST<double>::search(double);
template std::string BST<double>::print();
