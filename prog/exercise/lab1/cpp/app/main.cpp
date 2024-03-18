#include <iostream>
#include <cstdlib>
#include <sstream>

#include "valueConverter.hpp"

#include "headers.h"

int main(const int argc, const char argv[const])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n> <index1> <index2> ... <index_n>" << std::endl;
        return 1;
    }

    auto n = ValueConverter::stringToValue<int>(argv[1]);
    
    std::cout << "Prime numbers up to " << n << " are: " << std::endl;

}
