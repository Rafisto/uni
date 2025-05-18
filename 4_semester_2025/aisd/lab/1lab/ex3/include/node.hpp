#ifndef NODE_HPP
#define NODE_HPP

typedef unsigned int uint;

template <typename T>
struct Node
{
    T value;
    Node<T> *next = nullptr;
    Node<T> *prev = nullptr;

    Node(T new_value) : value(new_value) {}
    ~Node() = default;
};

#endif // NODE_HPP