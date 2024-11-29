/**
 * @file shell.h
 * @brief Header file for shell library.
 *
 * This file contains the necessary includes, definitions, and function
 * declarations for the shell library used in the project.
 */
#ifndef LSH_LIB_SHELL
#define LSH_LIB_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Exits the shell program.
 *
 * This function is responsible for terminating the shell program
 * and performing any necessary cleanup operations before exiting.
 */
void exit_shell();

/**
 * @brief Reads a command from the standard input.
 *
 * This function reads a command from the standard input and stores it
 * in the provided buffer.
 *
 * @param line The buffer where the command will be stored.
 */
void read_command(char *line);

#endif // LSH_LIB_SHELL