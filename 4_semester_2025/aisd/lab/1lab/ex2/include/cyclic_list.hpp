#ifndef CYCLIC_LIST_HPP
#define CYCLIC_LIST_HPP

#include "node.hpp"

template <typename T>
class List
{
public:
    size_t item_count = 0;
    Node<T> *list = nullptr;

    List() : item_count(0) {}
    ~List()
    {
        for (size_t i = 0; i < item_count; i++)
        {
            Node<T> *temp = list;
            list = list->next;
            delete temp;
        }
    }

    List(const List &other) : item_count(other.item_count), list(other.list) {}
    List &operator=(const List &other)
    {
        if (this != &other)
        {
            item_count = other.item_count;
            list = other.list;
        }
        return *this;
    }
};

template <typename T>
void insert(List<T> &l, T i) noexcept(true)
{
    l.item_count++;
    if (l.list == nullptr)
    {
        l.list = new Node<T>(i);
        l.list->next = l.list;
    }
    else
    {
        Node<T> *new_node = new Node<T>(i);
        Node<T> *first = l.list;
        Node<T> *last = l.list;
        for (size_t j = 1; j < l.item_count - 1; j++)
        {
            last = last->next;
        }

        new_node->next = first;
        last->next = new_node;
    }
}

template <typename T>
List<T> merge(List<T>* l1, List<T>* l2) noexcept(true)
{
    if (l1->list == nullptr)
        return *l2;

    if (l2->list == nullptr)
        return *l1;

    List<T> result = List<T>();
    Node<T> *last = l1->list;

    for (size_t i = 1; i < l1->item_count; i++)
    {
        last = last->next;
    }

    last->next = l2->list;

    for (size_t i = 0; i < l2->item_count; i++)
    {
        last = last->next;
    }

    last->next = l1->list;

    result.list = l1->list;
    return result;
}

#endif // CYCLIC_LIST_HPP