#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class FIFO {
    struct Node {
        std::shared_ptr<Node> next = nullptr;
        T value;

        Node(T new_value): value(new_value) {}
    };

    std::shared_ptr<Node> front = nullptr;
    std::shared_ptr<Node> back = nullptr;

    public:
    void push(T new_value) noexcept(true) {
        if (back == nullptr) {
            back = std::make_shared<Node>(new_value);
            front = back;
        }
        else {
            back->next = std::make_shared<Node>(new_value);
            back = back->next;
        }
    }

    T pop() noexcept(false) {
        if (front == nullptr) {
            throw std::underflow_error("No items left in queue");
        }

        T value = front->value;
        front = std::move(front->next); 

        return value;
    }
};

template <typename T>
class LIFO {
    struct Node {
        std::shared_ptr<Node> prev = nullptr;
        T value;

        Node(T new_value): value(new_value) {}
    };

    std::shared_ptr<Node> front = nullptr;
    std::shared_ptr<Node> back = nullptr;

    public:
    void push(T new_value) noexcept(true) {
        if (back == nullptr) {
            back = std::make_shared<Node>(new_value);
            front = back;
        }
        else {
            auto new_node = std::make_shared<Node>(new_value);
            new_node->prev = back;
            back = new_node;
        }
    }

    T pop() noexcept(false) {
        if (back == nullptr) {
            throw std::underflow_error("No items left in queue");
        }

        T value = back->value;
        back = back->prev;
        

        return value;
    }
};

void test_fifo() noexcept(true) {
    FIFO<int> fifo;
    for (int i = 0; i < 50; i++) {
        fifo.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }
    while (true) {
        try {
            std::cout << "Popped: " << fifo.pop() << std::endl;
        } catch (std::underflow_error& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

void test_lifo() noexcept(true) {
    LIFO<int> fifo;
    for (int i = 0; i < 50; i++) {
        fifo.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }
    while (true) {
        try {
            std::cout << "Popped: " << fifo.pop() << std::endl;
        } catch (std::underflow_error& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}


int main(void) noexcept(true) {
    test_fifo();
    test_lifo();
}