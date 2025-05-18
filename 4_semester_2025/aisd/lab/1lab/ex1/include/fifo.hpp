#ifndef FIFO_HPP
#define FIFO_HPP

template <typename T>
class FIFO
{
    struct Node
    {
        Node* next = nullptr;
        T value;

        explicit Node(T new_value) : value(new_value) {}
    };

    Node* front = nullptr;
    Node* back = nullptr;

public:
    FIFO() = default;
    ~FIFO() {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void push(T new_value)
    {
        Node* new_node = new Node(new_value);

        if (back == nullptr)
        {
            back = new_node;
            front = back;
        }
        else
        {
            back->next = new_node;
            back = new_node;
        }
    }

    T pop() noexcept(false)
    {
        if (front == nullptr)
        {
            throw std::underflow_error("No items left in queue");
        }

        T value = front->value;
        Node* temp = front;
        front = front->next;
        delete temp;

        return value;
    }
};

#endif // FIFO_HPP
