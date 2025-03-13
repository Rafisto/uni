#include <iostream>
#include <memory>

template <typename T>
struct Node {
        T value;
        std::shared_ptr<Node> next = nullptr;

        Node(T new_value): value(new_value) {}
    };

template <typename T>
class List {
public:
    size_t item_count = 0;
    std::shared_ptr<Node<T>> list = nullptr;

    List(): item_count(0) {}
};

template <typename T>
void insert(List<T>& l, T i) noexcept(true) {
    l.item_count++;
    if (l.list == nullptr) {
        l.list = std::make_shared<Node<T>>(i);
        l.list->next = l.list;
    } else {
        std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(i);
        std::shared_ptr<Node<T>> first = l.list;
        std::shared_ptr<Node<T>> last = l.list;
        for (int j = 1; j < l.item_count - 1; j++) {
            last = last->next;
        }

        new_node->next = first;
        last->next = new_node;
    }
}

template <typename T>
List<T> merge(List<T> l1, List<T> l2) noexcept(true) {
    if (l1.list == nullptr) return l2;
    if (l2.list == nullptr) return l1;
    
    List<T> result = List<T>();
    std::shared_ptr<Node<T>> last = l1.list;
    for (int i = 1; i < l1.item_count; i++) {
        last = last->next;
    }

    last->next = l2.list;
    for (int i = 0; i < l2.item_count; i++) {
        last = last->next;
    }

    last->next = l1.list;

    result.list = l1.list;
    result.item_count = l1.item_count + l2.item_count;

    return result; 
}

void test_inserts() {
    List<char> l = List<char>();

    std::cout << "Printing (a,b,c,d): ";

    insert(l, 'a');
    insert(l, 'b');
    insert(l, 'c');
    insert(l, 'd');

    std::shared_ptr<Node<char>> last = l.list;
    for (int i = 0; i < 6; i++) {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << std::endl;
}

typedef unsigned int uint;

void test_merges() {
    List<uint> l1 = List<uint>();
    for(uint i = 0; i < 10; i++) {
        insert(l1, i);
    }

    std::cout << "First list has been created: ";
    std::shared_ptr<Node<uint>> last = l1.list;
    for (int i = 0; i < l1.item_count; i++) {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << "(" << l1.item_count << ")" << std::endl;

    List<uint> l2 = List<uint>();
    for(uint i = 20; i < 30; i++) {
        insert(l2, i);
    }

    std::cout << "Second list has been created: ";
    last = l2.list;
    for (int i = 0; i < 10; i++) {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << std::endl;

    List<uint> l3 = merge(l1, l2);
    last = l3.list;

    std::cout << "Merged list: ";

    for (int i = 0; i < 45; i++) {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << std::endl;
}

int main(void) {
    test_inserts();
    test_merges();
}
