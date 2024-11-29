/**
 * @file internal.h
 *
 * @brief Header file for the internal commands.
 */
#ifndef LIB_LSH_INTERNAL
#define LIB_LSH_INTERNAL

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "types.h"

int shell_cd(char **args);
int shell_exit(char **args);
int shell_jobs(char **args);
int shell_fg(char **args);
int shell_bg(char **args);
int internal_command(char **args);

const internal_command_t commands[] = {
    {"cd", shell_cd},
    {"exit", shell_exit},
    {"jobs", shell_jobs},
    {"fg", shell_fg},
    {"bg", shell_bg},
    {NULL, NULL}};

/**
 * @brief Executes an internal command if it matches one of the predefined commands.
 *
 * This function iterates through a list of predefined commands and compares the
 * first argument in the provided args array with the name of each command. If a
 * match is found, the corresponding command function is executed with the args
 * array as its argument.
 *
 * @param args A null-terminated array of strings representing the command and its arguments.
 * @return int The return value of the executed command function if a match is found,
 *             or -1 if no matching command is found.
 */
int internal_command(char **args);

/**
 * @brief Changes the current working directory.
 *
 * This function changes the current working directory to the directory specified
 *
 * @param args A null-terminated array of strings representing the command and its arguments.
 * @return int The return value of the executed command function.
 */
int shell_cd(char **args);

/**
 * @brief Exits the shell program.
 *
 * This function is responsible for terminating the shell program
 * and performing any necessary cleanup operations before exiting.
 *
 * @param args A null-terminated array of strings representing the command and its arguments.
 * @return int The return value of the executed command function.
 */
int shell_exit(char **args);

#endif // LIB_LSH_INTERNAL