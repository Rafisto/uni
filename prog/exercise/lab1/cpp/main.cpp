#include <iostream>
#include <cstdlib>
#include <headers.h>

int parseIntArgv(const char *arg)
{
    char *endPtr;
    long number = std::strtol(arg, &endPtr, 10);
    if (*endPtr != '\0')
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Invalid argument: " + arg);
    }
    return static_cast<int>(number);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n> <index1> <index2> ... <index_n>" << std::endl;
        return 1;
    }

    try
    {
        int number = parseIntArgv(argv[1]);
        PrimeNumbers p(static_cast<int>(number));

        for (int i = 2; i < argc; ++i)
        {
            try
            {
                int arg = parseIntArgv(argv[i]);
                int result = p.getPrime(arg);
                if (result != -1)
                {
                    std::cout << arg << " - " << result << std::endl;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << __FILE__ << ":" << __LINE__ << " [" << __func__ << "] "
                          << e.what() << std::endl;
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << __FILE__ << ":" << __LINE__ << " [" << __func__ << "] "
                  << "Failed to create Prime Numbers object" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
