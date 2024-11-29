/**
 * @file tokenizer.h
 * @brief Header file for the tokenizer library.
 *
 * This file contains the declarations and macros for the tokenizer library.
 * The tokenizer library is used to split strings into tokens based on specified delimiters.
 *
 * @note Ensure to include this header file in your source files to use the tokenizer functions.
 */
#ifndef LSH_LIB_TOKENIZER
#define LSH_LIB_TOKENIZER

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "types.h"

/**
 * @brief Tokenizes a shell command line into arguments, handles pipes, and file descriptor redirections.
 *
 * This function tokenizes a command line string into individual arguments,
 * processes pipe-separated commands into a chain of `shell_request_t`
 * structures, and identifies file descriptor redirections.
 *
 * @param line The command line string to be tokenized.
 * @param request A pointer to the first shell_request_t structure where the
 *                tokenized arguments and redirections will be stored.
 */
void tokenize_shell_args(char *line, shell_request_t *request);

/**
 * @brief Tokenizes a command line string into executable arguments.
 *
 * This function takes a command line string and splits it into individual
 * arguments suitable for execution. The arguments are stored in the provided
 * argv array, and the number of arguments is stored in argc.
 *
 * @param line The command line string to be tokenized.
 * @param argv An array of strings where the tokenized arguments will be stored.
 *             This array should be pre-allocated with enough space to hold all
 *             the arguments.
 * @param argc A pointer to an integer where the number of arguments will be stored.
 */
void tokenize_exec_args(char *line, char **argv, int *argc);

#endif // LSH_LIB_TOKENIZER