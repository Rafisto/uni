#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <internal.h>
#include <types.h>
#include <jobs.h>

int internal_command(char **args)
{
    for (int i = 0; commands[i].name != NULL; i++)
    {
        if (strcmp(args[0], commands[i].name) == 0)
        {
            return commands[i].func(args);
        }
    }
    return -1; // Not an internal command
}

int shell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
            return 1;
        }
        return 0;
    }
    return 1;
}

int shell_exit(char **args)
{
    return 0;
}

int shell_jobs(char **args)
{
    job_list(); // Call the job manager's function to list jobs
    return 0;
}

// Bring a job to the foreground (`fg`)
int shell_fg(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"fg\"\n");
        return 1;
    }
    pid_t pid = (pid_t)atoi(args[1]); // Convert argument to PID
    if (job_fg(pid) != 0)
    {
        fprintf(stderr, "lsh: job %d not found\n", pid);
        return 1;
    }
    return 0;
}

// Send a job to the background (`bg`)
int shell_bg(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"bg\"\n");
        return 1;
    }
    pid_t pid = (pid_t)atoi(args[1]); // Convert argument to PID
    if (job_bg(pid) != 0)
    {
        fprintf(stderr, "lsh: job %d not found\n", pid);
        return 1;
    }
    return 0;
}