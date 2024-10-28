#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>

// rdr.c - redirect file descriptor to a different device for a given process
int main(int argc, char* argv[])
{
    int opt;
    pid_t pid = -1;
    int input = -1;
    char *output = NULL;

    while ((opt = getopt(argc, argv, "p:i:o:")) != -1)
    {
        switch (opt)
        {
            case 'p':
                pid = atoi(optarg);
                break;
            case 'i':
                input = atoi(optarg);
                break;
            case 'o':
                output = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -p [pid] -i [input] -o [output]\n", argv[0]);
                return 1;
        }
    }

    if (pid == -1 || input == -1 || output == NULL)
    {
        fprintf(stderr, "Usage: %s -p [pid] -i [input] -o [output]\n", argv[0]);
        return 1;
    }

    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
        perror("ptrace");
    }

    // TODO: Implement the redirection
}