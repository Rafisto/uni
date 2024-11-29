/**
 * @file types.h
 * @brief This header file contains various types used in the lsh shell.
 */

#ifndef LSH_LIB_TYPES
#define LSH_LIB_TYPES

#include <sys/types.h>
#include <stdbool.h>

/**
 * @typedef fd_redirect_t
 * @brief A structure to represent file descriptor redirection.
 *
 * This structure represents a file descriptor redirection, containing the input and output
 * file descriptors that should be redirected.
 *
 * @param input The initial file descriptor.
 * @param output Redirected file descriptor.
 */
typedef struct
{
    int input;
    int output;
} fd_redirect_t;

/**
 * @typedef shell_request_t
 * @brief A structure to represent a shell request.
 *
 * This structure represents a shell request, containing the command arguments,
 * their number and additional properties, such as backgrond or pipe, redirect, definitions.
 *
 * @param args An array of strings representing the command arguments.
 * @param argc The number of arguments in the args array.
 * @param background (default false) a boolean value indicating whether
 * @param next A pointer to the next shell_request_t structure in case of pipe.
 * @param fd_redirect A list of file descriptors to redirect.
 * the command should be executed in the background.
 */
typedef struct
{
    char *args[128];
    int argc;
    bool background;
    void *next;
    fd_redirect_t fd_redirect[64];
} shell_request_t;

/**
 * @typedef internal_command_func_t
 * @brief A function pointer type for command functions.
 *
 * This type defines a function pointer for functions to
 * take an array of arguments and return an integer status code.
 *
 * @param args An array of strings representing the command arguments.
 * @return An integer status code indicating the result of the command execution.
 *
 * @see shell_request_t
 * @see shell.h
 */
typedef int (*internal_command_func_t)(char **args);

/**
 * @typedef internal_command_t
 * @brief A structure to represent an internal shell command.
 *
 * This structure represents an internal shell command, containing the command name
 * and a pointer to the function that should be executed when the command is called.
 *
 * The arguments are passed automatically through the shell_request_t structure.
 *
 * @see shell_request_t
 * @see shell.h
 * @see tokenizer.h
 */
typedef struct
{
    const char *name;
    internal_command_func_t func;
} internal_command_t;

#endif // LSH_LIB_TYPES