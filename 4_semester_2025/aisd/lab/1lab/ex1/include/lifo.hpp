#ifndef LIFO_HPP
#define LIFO_HPP

template <typename T>
class LIFO
{
    struct Node
    {
        Node* prev = nullptr;
        T value;

        explicit Node(T new_value) : value(new_value) {}
    };

    Node* front = nullptr;
    Node* back = nullptr;

public:
    LIFO() = default;
    ~LIFO() {
        while (back != nullptr)
        {
            Node* temp = back;
            back = back->prev;
            delete temp;
        }
    }

    void push(T new_value) noexcept(true)
    {
        Node* new_node = new Node(new_value);

        if (back == nullptr)
        {
            back = new_node;
            front = back;
        }
        else
        {
            new_node->prev = back;
            back = new_node;
        }
    }

    T pop() noexcept(false)
    {
        if (back == nullptr)
        {
            throw std::underflow_error("No items left in stack");
        }

        T value = back->value;
        Node* temp = back;
        back = back->prev;
        delete temp;

        return value;
    }
};

#endif // LIFO_HPP
