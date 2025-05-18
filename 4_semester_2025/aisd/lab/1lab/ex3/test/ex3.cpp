#include <cstdint>
#include <ctime>
#include <iostream>
#include <vector>

#include <node.hpp>
#include <cyclic_list.hpp>

void test_inserts() noexcept(true);
void test_merges() noexcept(true);
void test_array() noexcept(true);

void test_inserts() noexcept(true)
{
    List<char> l = List<char>();

    std::cout << "Printing (a,b,c,d): ";

    insert(l, 'a');
    insert(l, 'b');
    insert(l, 'c');
    insert(l, 'd');

    Node<char> *last = l.list;
    for (size_t i = 0; i < 6; i++)
    {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << std::endl;
}

void test_merges() noexcept(true)
{
    List<uint> l1;

    for (uint i = 10; i < 20; i++)
    {
        insert(l1, i);
    }

    std::cout << "First list has been created: ";
    Node<uint> *last = l1.list;
    for (uint i = 0; i < l1.item_count; i++)
    {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << "(" << l1.item_count << ")" << std::endl;

    List<uint> l2;
    for (uint i = 40; i < 50; i++)
    {
        insert(l2, i);
    }

    std::cout << "Second list has been created: ";
    last = l2.list;
    for (int i = 0; i < 10; i++)
    {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << "(" << l2.item_count << ")" << std::endl;

    merge(&l1, &l2);

    std::cout << "Merged list: ";

    last = l1.list;
    for (size_t i = 0; i < l1.item_count; i++)
    {
        std::cout << last->value << " ";
        last = last->next;
    }

    std::cout << "..." << std::endl;
}

void test_array() noexcept(true)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<uint> varray;
    List<uint> larray = List<uint>();

    for (size_t i = 0; i < 10000; ++i)
    {
        uint32_t randomNumber = static_cast<uint32_t>(std::rand() % 100001);
        varray.push_back(randomNumber);
        insert(larray, randomNumber);
    }

    int avg = 0;

    for (size_t i = 0; i < 1000; i++)
    {
        int direction = std::rand() % 2;
        int count = 0;
        uint32_t randomNumber = varray[static_cast<size_t>(std::rand() % 10000)];
        for (size_t j = 0; j < 10000; j++)
        {
            while (larray.list->value != randomNumber)
            {
                count++;
                if (direction == 0)
                    larray.list = larray.list->next;

                else
                    larray.list = larray.list->prev;
            }
        }
        avg += count;
    }

    std::cout << "avgsc (random 'T' member): " << avg / 1000 << std::endl;

    avg = 0;

    for (int i = 0; i < 1000; i++)
    {
        int direction = std::rand() % 2;
        int count = 0;
        uint32_t randomNumber = static_cast<uint32_t>(std::rand() % 100001);
        for (int j = 0; j < 10000; j++)
        {
            while (larray.list->value != randomNumber)
            {
                if (count == 10000)
                    break;

                count++;

                if (direction == 0)
                    larray.list = larray.list->next;

                else
                    larray.list = larray.list->prev;
            }
        }
        avg += count;
    }

    std::cout << "avgsc (random 'I' member): " << avg / 1000 << std::endl;
}

int main(void)
{
    test_inserts();
    test_merges();
    test_array();
}
