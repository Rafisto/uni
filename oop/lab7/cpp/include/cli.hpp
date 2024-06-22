#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <sstream>

#include <bst.hpp>
#include <stringConverter.hpp>

template <typename T>
class CLI {
public:
    BST<T> tree;
    CLI() {
        tree = BST<T>();
    }

    void run() {
        std::string command;
        std::cin.ignore();
        bool running = true;

        while (running) {
            std::cout << "Enter a command: ";
            std::string command;
            std::getline(std::cin, command); 

            std::cout << "Command: " << command << std::endl;

            if (command == "p") {
                std::cout << "Printing the tree" << std::endl;
                std::cout << tree.print() << std::endl;
                continue;
            }

            std::istringstream iss(command);
            std::string operation;
            std::string value;

            if (!(iss >> operation >> value)) {
                std::cout << "Invalid command. Please specify a command and a value to insert." << std::endl;
                continue;
            }

            T convertedValue = StringConverter::stringToVal<T>(value);

            if (operation == "i" || operation == "a") {
                tree.insert(convertedValue);
            } else if (operation == "r" || operation == "d") {
                tree.remove(convertedValue);
            } else if (operation == "s" || operation == "f") {
                bool found = tree.search(convertedValue);
                std::cout << "Value " << value << " is " << (found ? "in" : "not in") << " the tree." << std::endl;
            } else {
                std::cout << "Invalid command." << std::endl;
            }
        }
    }
};

template class CLI<int>;
template class CLI<std::string>;
template class CLI<double>;

#endif // CLI_HPP
