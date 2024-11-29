#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <responses.h>

void print_welcome_message()
{
    printf("%s", WELCOME_MESSAGE);
}

void print_goodbye_message()
{
    printf("%s", GOODBYE_MESSAGE);
}

void print_prompt()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char *last_part = strrchr(cwd, '/');
        if (last_part != NULL)
        {
            last_part++;
        }
        else
        {
            last_part = cwd;
        }
        printf("%s[%s]%s", PROMPT, last_part, PROMPT_SUFFIX);
    }
    else
    {
        perror("getcwd() error");
    }
}

void print_command_not_found()
{
    printf("%s", COMMAND_NOT_FOUND);
}
