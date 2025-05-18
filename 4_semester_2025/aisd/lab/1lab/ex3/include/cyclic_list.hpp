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
    Node<T> *new_node = new Node<T>(i);

    l.item_count++;

    if (l.list == nullptr)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        l.list = new_node;
    }
    else
    {
        new_node->prev = l.list;
        new_node->next = l.list->next;
        l.list->next->prev = new_node;
        l.list->next = new_node;
    }
}

template <typename T>
void merge(List<T>* l1, List<T>* l2) noexcept(true)
{
    if (l1->list == nullptr)
    {
        l1->list = l2->list;
        l1->item_count = l2->item_count;
        l2->list = nullptr;
        l2->item_count = 0;
        return;
    }
    if (l2->list == nullptr)
        return;

    l1->list->prev->next = l2->list;
    l2->list->prev->next = l1->list;

    Node<T> *temp = l1->list->prev;
    l1->list->prev = l2->list->prev;
    l2->list->prev = temp;

    l1->item_count += l2->item_count;

    l2->list = nullptr;
    l2->item_count = 0;
}

#endif // CYCLIC_LIST_HPP