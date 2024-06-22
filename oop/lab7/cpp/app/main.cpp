#include <iostream>
#include <cli.hpp>

int main() {
    std::cout << "Which tree type do you want to create?" << std::endl;
    std::cout << "(i)nteger, (d)ouble, (s)tring" << std::endl;
    char type;
    std::cin >> type;
    switch(type) {
        case 'i': {
            std::cout << "Creating integer tree" << std::endl;
            CLI<int> intCLI{};
            intCLI.run();
            break;
        }
        case 'd': {
            std::cout << "Creating double tree" << std::endl;
            CLI<double> doubleCLI{};
            doubleCLI.run();
            break;
        }
        case 's': {
            std::cout << "Creating string tree" << std::endl;
            CLI<std::string> stringCLI{};
            stringCLI.run();
            break;
        }
        default:
            std::cout << "Invalid type" << std::endl;
    }
    return 0;
}
