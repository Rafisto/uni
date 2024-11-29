#include <shell.h>
#include <responses.h>

void exit_shell()
{
    print_goodbye_message();
    exit(0);
}

void read_command(char *line)
{
    if (!fgets(line, 1024, stdin))
    {
        exit_shell();
    }

    if (strcmp(line, "exit\n") == 0)
    {
        exit_shell();
    }

    if (strcmp(line, "\n") == 0)
    {
        return;
    }
}