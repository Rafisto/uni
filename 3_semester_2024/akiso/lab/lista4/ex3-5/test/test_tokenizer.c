#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tokenizer.h"
#include "types.h"

void test_tokenize_shell_args() {
    char line[] = "ls -l | grep .c > output.txt";
    shell_request_t request;
    tokenize_shell_args(line, &request);

    // Test first command
    assert(request.argc == 2);
    assert(strcmp(request.args[0], "ls") == 0);
    assert(strcmp(request.args[1], "-l") == 0);
    assert(request.args[2] == NULL);

    // Test pipe
    assert(request.next != NULL);

    // Test second command
    shell_request_t *second_request = (shell_request_t*) request.next;
    assert(second_request->argc == 2);
    assert(strcmp(second_request->args[0], "grep") == 0);
    assert(strcmp(second_request->args[1], ".c") == 0);
    assert(second_request->args[2] == NULL);

    // Test redirection
    assert(second_request->fd_redirect[0].input == STDOUT_FILENO);
    assert(second_request->fd_redirect[0].output != -1);
    assert(second_request->fd_redirect[1].input == -1);
    assert(second_request->fd_redirect[1].output == -1);

    // Test no background
    assert(!request.background);
    assert(!second_request->background);
}

void test_tokenize_exec_args() {
    char line[] = "gcc -o output main.c";
    char *argv[10];
    int argc;
    tokenize_exec_args(line, argv, &argc);

    // Test arguments
    assert(argc == 4);
    assert(strcmp(argv[0], "gcc") == 0);
    assert(strcmp(argv[1], "-o") == 0);
    assert(strcmp(argv[2], "output") == 0);
    assert(strcmp(argv[3], "main.c") == 0);
    assert(argv[4] == NULL);
}

int main() {
    printf("Running tests...\n");

    printf("Testing tokenize_shell_args...\n");
    test_tokenize_shell_args();

    printf("Testing tokenize_exec_args...\n");
    test_tokenize_exec_args();

    // delete output.txt
    remove("output.txt");

    printf("All tests passed!\n");
    return 0;
}