#include <iostream>
#include <memory>
#include <stdexcept>

#include <fifo.hpp>
#include <lifo.hpp>

void test_fifo() noexcept(true);
void test_lifo() noexcept(true);

void test_fifo() noexcept(true)
{
    FIFO<int> fifo;
    for (int i = 0; i < 50; i++)
    {
        fifo.push(i);
        std::cout << "FIFO Pushed: " << i << std::endl;
    }
    while (true)
    {
        try
        {
            std::cout << "FIFO Popped: " << fifo.pop() << std::endl;
        }
        catch (std::underflow_error &e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

void test_lifo() noexcept(true)
{
    LIFO<int> lifo;
    for (int i = 0; i < 50; i++)
    {
        lifo.push(i);
        std::cout << "LIFO Pushed: " << i << std::endl;
    }
    while (true)
    {
        try
        {
            std::cout << "LIFO Popped: " << lifo.pop() << std::endl;
        }
        catch (std::underflow_error &e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

int main(void) noexcept(true)
{
    test_fifo();
    test_lifo();
}
