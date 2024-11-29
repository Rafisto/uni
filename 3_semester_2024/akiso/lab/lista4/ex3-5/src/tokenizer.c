#include <tokenizer.h> 
#include <types.h>

void tokenize_shell_args(char *line, shell_request_t *request)
{
    request->argc = 0;
    request->background = false;
    request->next = NULL;

    int redirect_count = 0; // Keep track of redirections in the current request
    shell_request_t *current_request = request;

    char *token = strtok(line, " \n");
    char *last_token = NULL;

    while (token != NULL)
    {
        if (strcmp(token, "|") == 0)
        {
            // End current command's arguments and create a new shell_request
            current_request->args[current_request->argc] = NULL;

            shell_request_t *new_request = (shell_request_t *)malloc(sizeof(shell_request_t));
            new_request->argc = 0;
            new_request->background = false;
            new_request->next = NULL;
            current_request->next = new_request;
            current_request = new_request;

            redirect_count = 0; // Reset redirection count for the new command
        }
        else if (strcmp(token, ">") == 0 || strcmp(token, "<") == 0 || strncmp(token, "2>", 2) == 0)
        {
            // Handle redirection operators
            char *filename = strtok(NULL, " \n");
            if (filename == NULL)
            {
                fprintf(stderr, "Error: Missing file for redirection operator %s\n", token);
                return;
            }

            if (redirect_count >= 64)
            {
                fprintf(stderr, "Error: Too many redirections\n");
                return;
            }

            if (strcmp(token, ">") == 0)
            {
                current_request->fd_redirect[redirect_count].input = STDOUT_FILENO;
                current_request->fd_redirect[redirect_count].output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            else if (strcmp(token, "<") == 0)
            {
                current_request->fd_redirect[redirect_count].input = STDIN_FILENO;
                current_request->fd_redirect[redirect_count].output = open(filename, O_RDONLY);
            }
            else if (strncmp(token, "2>", 2) == 0)
            {
                current_request->fd_redirect[redirect_count].input = STDERR_FILENO;
                current_request->fd_redirect[redirect_count].output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }

            if (current_request->fd_redirect[redirect_count].output == -1)
            {
                perror("Error opening file for redirection");
                return;
            }

            redirect_count++;
        }
        else
        {
            // Regular argument
            last_token = token;
            current_request->args[current_request->argc++] = token;
        }
        token = strtok(NULL, " \n");
    }

    // Finalize the last command
    if (last_token && strcmp(last_token, "&") == 0)
    {
        current_request->background = true;
        current_request->args[--current_request->argc] = NULL;
    }
    else
    {
        current_request->args[current_request->argc] = NULL;
    }

    // Null-terminate redirection list
    current_request->fd_redirect[redirect_count].input = -1;
    current_request->fd_redirect[redirect_count].output = -1;
}

void tokenize_exec_args(char *line, char **argv, int *argc)
{
    int i = 0;
    char *token = strtok(line, " \n");
    while (token != NULL)
    {
        argv[i++] = token;
        token = strtok(NULL, " \n");
    }
    argv[i] = NULL;
}