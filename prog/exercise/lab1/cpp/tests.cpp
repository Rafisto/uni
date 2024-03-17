#include <iostream>
#include <vector>
#include <stdexcept>

#include "primes_library/primes_library.h"

#include "headers.h"

void testConstructor();
void testGetPrime();

void testConstructor()
{
    {
        try
        {
            PrimeNumbers primeObj(10);
            std::cout << "[+] Test Constructor: Passed (Valid input)\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "[-] Test Constructor: Failed (Valid input): " << e.what() << '\n';
        }
    }

    {
        try
        {
            PrimeNumbers primeObj(1);
            std::cerr << "[-] Test except Constructor: Failed (Invalid argument)\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "[+] Test except Constructor: Passed (Invalid argument): " << e.what() << '\n';
        }
    }
}

void testGetPrime()
{
    PrimeNumbers primeObj(10);
    {
        int result = primeObj.getPrime(3);
        if (result == 7)
            std::cout << "[+] Test getPrime: Passed (Valid index)\n";
        else
            std::cerr << "[-] Test getPrime: Failed (Valid index): Expected 7, got " << result << '\n';
    }

    {
        try
        {
            primeObj.getPrime(-1);
            std::cerr << "[-] Test except getPrime: Failed (Invalid argument)\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "[+] Test except getPrime: Passed (Invalid argument): " << e.what() << '\n';
        }
    }

    {
        try
        {
            primeObj.getPrime(20);
            std::cerr << "[-] Test except getPrime: Failed (Invalid argument)\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "[+] Test except getPrime: Passed (Invalid argument): " << e.what() << '\n';
        }
    }
}

int main()
{
    testConstructor();
    testGetPrime();
    return 0;
}
