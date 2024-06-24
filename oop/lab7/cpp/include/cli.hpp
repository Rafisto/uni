#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <sstream>

#include <bst.hpp>
#include <stringConverter.hpp>

/**
 * @class CLI
 * @brief Command Line Interface for interacting with a Binary Search Tree.
 * 
 * The CLI class provides a command line interface for performing operations on a Binary Search Tree (BST).
 * It allows the user to insert, remove, search, and print the elements of the BST.
 */
template <typename T>
class CLI {
public:
    BST<T> tree;
    CLI() {
        tree = BST<T>();
    }

    /**
     * Runs the command line interface.
     */
    void run() {
        std::string command;
        std::cin.ignore();

        while (true) {
            std::cout << "Enter a command: ";
            std::getline(std::cin, command); 

            if (!std::cin) {
                std::cout << "You want to quit! Go ahead." << std::endl;
                break;
            }

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

            T convertedValue;

            try { 
                convertedValue = StringConverter::stringToVal<T>(value);
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
                continue;
            }

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

        tree.freeTree();
    }
};

template class CLI<int>;
template class CLI<std::string>;
template class CLI<double>;

#endif // CLI_HPP
