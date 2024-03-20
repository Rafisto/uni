#include <iostream>
#include <vector>

#include <stringConverter.hpp>
#include <primeNumbers.hpp>

/**
 * @brief Main function
 *
 * @param argc - number of arguments
 * @param argv - array of arguments
 * @return int
 */
int main(const int argc, const char *const argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2> ..." << std::endl;
        return 1;
    }

    PrimeNumbers* p;

    try
    {
        const auto initArgument = StringConverter::stringToVal<int>(std::string(argv[1]));
        p = new PrimeNumbers(initArgument);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid Argument Error: " << e.what() << " should be greater than 1" << std::endl;
        return 1;
    }

    std::cout << "Successfully initialized PrimeNumbers object of count " << std::to_string(p->getCount()) << std::endl;

    for (std::size_t i = 2; i < static_cast<std::size_t>(argc); i++)
    {
        try
        {
            const auto argNumber = StringConverter::stringToVal<int>(std::string(argv[i]));
            const auto prime = p->getPrime(argNumber);

            std::cout << std::to_string(argNumber) << " --> " << std::to_string(prime) << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Out of Range Error: " << e.what() << std::endl;
        }
    }

    delete p;

    return 0;
}