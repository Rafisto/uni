/*
    Rafał Włodarczyk
    rdr.c - redirect file descriptor to a different device for a given process
*/

#include <stdio.h>
#include <stdlib.h>

#include "utils/macros.h"
#include "utils/redirect.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
        rfail("Usage: %s [pid] [input] [output]", argv[0]);

    pid_t pid = atoi(argv[1]);
    int input = atoi(argv[2]);
    char *output = argv[3];

    if (pid <= 0 || input < 0 || output == NULL)
        rfail("Invalid arguments. Usage: %s [pid] [input] [output]", argv[0]);

    rinfo("Redirecting file descriptor %d to %s for process %d", input, output, pid);

    redirect(pid, input, output);
    return 0;
}
