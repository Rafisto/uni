package view;

import model.BST;
import parsers.*;

import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * The `CLI` (Command Line Interface) class is responsible for interacting with the user through the command line
 * and executing commands based on the user input. It uses a binary search tree (`BST`) to store and manipulate data.
 * The `CLI` class requires a parser (`Parser`) to parse user commands.
 *
 * @param <T> the type of elements stored in the binary search tree
 */
public class CLI<T extends Comparable<T>> {
    public BST<T> tree;
    public Parser<T> parser;

    /**
     * Constructs a new CLI (Command Line Interface) object with the specified parser.
     * The CLI is responsible for interacting with the user through the command line
     * and executing commands based on the user input.
     *
     * @param p the parser used to parse user commands
     */
    public CLI(Parser<T> p) {
        this.tree = new BST<T>();
        this.parser = p;
    }

    /**
     * Runs the command-line interface (CLI) for interacting with the tree.
     * The CLI prompts the user for commands and performs the corresponding operations on the tree.
     * Valid commands include:
     * - "p" to print the tree
     * - "i" or "a" followed by a value to insert the value into the tree
     * - "r" or "d" followed by a value to delete the value from the tree
     * - "s" or "f" followed by a value to search for the value in the tree
     * Invalid commands will display an error message.
     * The CLI continues running until the user chooses to quit.
     */
    public void run() {
        Scanner scanner = new Scanner(System.in);
        boolean running = true;

        while (running) {
            System.out.print("Enter a command: ");
            String command = null;

            try {
                command = scanner.nextLine();
            }
            catch(NoSuchElementException e) {
                System.out.println("Quit on CTRL+D");
                System.exit(0);
            }

            if (command.equals("p")) {
                System.out.println("Printing a tree");
                System.out.println(tree.print());
                continue;
            }

            String[] parts = command.split("\\s+");

            if (parts.length != 2) {
                System.out.println("Invalid command. Please specify a command and a value to insert.");
                continue;
            }

            String operation = parts[0];
            T value = null;

            try {
                value = parser.parse(parts[1]);
            } catch (NumberFormatException e) {
                System.out.println("Invalid value. Please specify a command and a value to insert.");
                continue;
            }

            switch (operation) {
                case "i":
                case "a":
                    tree.insert(value);
                    break;
                case "r":
                case "d":
                    tree.delete(value);
                    break;
                case "s":
                case "f":
                    boolean found = tree.search(value);
                    System.out.println("Value " + value + " is " + (found ? "in" : "not in") + " the tree.");
                    break;
                default:
                    System.out.println("Invalid command.");
                    break;
            }
        }

        scanner.close();
    }
}
