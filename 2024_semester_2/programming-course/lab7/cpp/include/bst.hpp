#ifndef BST_HPP
#define BST_HPP

#include <string>

#include <iostream>

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

    void insertNode(Node* node, T value);
    Node* deleteNode(Node* node, T value);
    bool searchRecursive(Node* node, T value);
    std::string printRecursive(Node* node, int indent);

public:
    BST() : root(nullptr) {}
    void insert(T value);
    void remove(T value);
    bool search(T value);
    std::string print();
};

template class BST<int>;
template class BST<std::string>;
template class BST<double>;

#endif // BST_HPP