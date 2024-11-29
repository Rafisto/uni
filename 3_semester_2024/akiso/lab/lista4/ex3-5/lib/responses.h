/**
 * @file responses.h
 * @brief This header file contains functions for printing various messages used in the lsh shell.
 *
 * The functions included are:
 * - print_welcome_message: Prints a welcome message to the user.
 * - print_goodbye_message: Prints a goodbye message to the user.
 * - print_prompt: Prints the shell prompt.
 * - print_command_not_found: Prints a message indicating that the entered command was not found.
 */
#ifndef LSH_LIB_RESPONSES
#define LSH_LIB_RESPONSES

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define WELCOME_MESSAGE "Welcome to lsh.\nType 'exit' or 'CTRL+D' to exit.\n"
#define GOODBYE_MESSAGE "Goodbye!\n"
#define PROMPT "lsh"
#define PROMPT_SUFFIX "> "
#define COMMAND_NOT_FOUND "Command not found\n"

/**
 * @brief Prints a welcome message to the user.
 */
void print_welcome_message();

/**
 * @brief Prints a goodbye message to the console.
 */
void print_goodbye_message();

/**
 * @brief Prints the shell prompt.
 */
void print_prompt();

/**
 * @brief Prints a message indicating that the entered command was not found.
 */
void print_command_not_found();

#endif // LSH_LIB_RESPONSES