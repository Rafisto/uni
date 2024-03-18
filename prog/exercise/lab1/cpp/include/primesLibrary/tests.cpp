#include <iostream>
#include <vector>
#include <stdexcept>

#include "primes_library.h"

void runSieveTests()
{
    {
        std::vector<int> expected_10 = {2, 3, 5, 7};
        std::vector<int> result_10 = PrimesLib::Sieve(10);
        if (result_10 == expected_10)
            std::cout << "Test for n = 10 passed.\n";
        else
            std::cout << "Test for n = 10 failed.\n";
    }

    {
        std::vector<int> expected_20 = {2, 3, 5, 7, 11, 13, 17, 19};
        std::vector<int> result_20 = PrimesLib::Sieve(20);
        if (result_20 == expected_20)
            std::cout << "Test for n = 20 passed.\n";
        else
            std::cout << "Test for n = 20 failed.\n";
    }

    {
        std::vector<int> expected_2 = {2};
        std::vector<int> result_2 = PrimesLib::Sieve(2);
        if (result_2 == expected_2)
            std::cout << "Test for n = 2 passed.\n";
        else
            std::cout << "Test for n = 2 failed.\n";
    }

    {
        try
        {
            PrimesLib::Sieve(1);
            std::cout << "Test for n = 1 failed. Expected exception not thrown.\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Test for n = 1 passed. Exception caught: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cout << "Test for n = 1 failed. Unexpected exception caught.\n";
        }
    }

    {
        try
        {
            std::vector<int> result = PrimesLib::Sieve(0);
            if (result.empty())
                std::cout << "Test for negative input passed.\n";
            else
                std::cout << "Test for negative input failed. Expected empty result for negative input.\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Test for negative input passed. Exception caught: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cout << "Test for negative input failed. Unexpected exception caught.\n";
        }
    }
}

int main()
{
    runSieveTests();
    return 0;
}
