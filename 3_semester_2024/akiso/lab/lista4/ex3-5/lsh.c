#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include <internal.h>
#include <responses.h>
#include <tokenizer.h>
#include <shell.h>
#include <types.h>
#include <jobs.h>

#define MAX_COMMAND_LENGTH 1024
int child_pid = -1;

// SIGINT handler for job control (CTRL+C)
void handle_sigint(int sig)
{
    if (child_pid > 0)
    {
        // Send SIGTERM to the child process (the foreground process)
        kill(child_pid, SIGTERM);
        waitpid(child_pid, NULL, WUNTRACED); // Wait for child to terminate
    }
}

// SIGTSTP handler to prevent parent from quitting (CTRL+Z)
void handle_sigtstp(int sig)
{
    if (child_pid > 0)
    {
        pid_t pid = getpid();
        job_suspend(pid);
        printf("\nJob with PID %d suspended and sent to background\n", pid);
    }
}

// SIGCHLD handler to handle child process termination
void handle_sigchld(int sig)
{
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status))
        {
            job_remove(pid);
        }
    }
}

// Main shell execution loop
int main()
{
    // Register SIGINT (CTRL+C) and SIGTSTP (CTRL+Z) handlers
    signal(SIGINT, handle_sigint);   // Register SIGINT handler (CTRL+C)
    signal(SIGTSTP, handle_sigtstp); // Register SIGTSTP handler (CTRL+Z)
    signal(SIGCHLD, handle_sigchld); // Register SIGCHLD handler
    char line[MAX_COMMAND_LENGTH];
    shell_request_t *root_cmd;
    shell_request_t cmd;

    int rc;
    int pipefd[2];
    int input_fd = 0;

    print_welcome_message(); // Print shell welcome message

    while (1)
    {
        print_prompt();     // Display the shell prompt
        read_command(line); // Read command line input
        if (strcmp(line, "\n") == 0)
            continue; // Skip if empty line

        tokenize_shell_args(line, &cmd); // Tokenize input into command structure
        root_cmd = &cmd;

        for (shell_request_t *current_cmd = &cmd; current_cmd != NULL; current_cmd = (shell_request_t *)current_cmd->next)
        {
            int internal = internal_command(current_cmd->args); // Check if it's an internal command

            if (internal == 0) // Internal command (no forking)
                continue;
            else if (internal == -1) // External command (needs forking)
            {
                if (current_cmd->next != NULL) // If there's a pipe, create a pipe
                {
                    if (pipe(pipefd) == -1)
                    {
                        perror("pipe");
                        exit(1);
                    }
                }

                child_pid = fork(); // Create a new child process

                if (child_pid < 0)
                {
                    perror("fork");
                    exit(1);
                }
                else if (child_pid == 0) // Child process
                {
                    // Redirect input if necessary
                    if (input_fd != STDIN_FILENO)
                    {
                        dup2(input_fd, STDIN_FILENO);
                        close(input_fd);
                    }

                    // Redirect output to pipe if there's a next command
                    if (current_cmd->next != NULL)
                    {
                        dup2(pipefd[1], STDOUT_FILENO);
                        close(pipefd[0]);
                        close(pipefd[1]);
                    }

                    // Apply file redirections
                    for (int i = 0; i < 64; i++)
                    {
                        if (current_cmd->fd_redirect[i].output != 0)
                        {
                            dup2(current_cmd->fd_redirect[i].output, current_cmd->fd_redirect[i].input);
                            close(current_cmd->fd_redirect[i].output);
                        }
                    }

                    // Execute the external command
                    rc = execvp(current_cmd->args[0], current_cmd->args);
                    if (rc == -1)
                    {
                        perror("execvp");
                        exit(1);
                    }
                }
                else // Parent process
                {
                    // If the command is not in the background, wait for it to finish
                    if (!current_cmd->background)
                    {
                        job_add(child_pid, current_cmd->args[0]); // Add job to job list
                        int status;
                        waitpid(child_pid, &status, WUNTRACED); // Wait for foreground job
                        if (WIFSTOPPED(status))
                        {
                            job_suspend(child_pid); // Suspend job if it's stopped
                        }
                        else
                        {
                            job_remove(child_pid); // Remove job from list after it finishes
                        }
                    }
                    else
                    {
                        job_add(child_pid, current_cmd->args[0]); // Add background job
                        printf("Job [%d] running in background\n", child_pid);
                    }

                    // Close the write end of the pipe in the parent
                    if (current_cmd->next != NULL)
                    {
                        close(pipefd[1]);
                    }

                    // Update input_fd for the next command in the pipeline
                    if (current_cmd->next != NULL)
                    {
                        input_fd = pipefd[0];
                    }
                }
            }
        }
    }

    // Cleanup dynamic memory
    for (shell_request_t *req = root_cmd; req != NULL; req = (shell_request_t *)req->next)
    {
        free(req);
    }

    // Cleanup job manager resources
    job_manager_cleanup();

    return 0;
}
