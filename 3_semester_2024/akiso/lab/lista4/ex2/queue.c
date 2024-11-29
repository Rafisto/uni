#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define SIGNAL_TO_SEND SIGUSR1

int main()
{
    int pid;
    printf("Enter the PID of the process you want to kill: ");
    scanf("%d", &pid);
    // send SIGUSR1 multiple times
    for (int i = 0; i < 5; i++)
    {
        printf("Sending SIGUSR1 to the process with PID: %d\n", pid);
        kill(pid, SIGNAL_TO_SEND);
    }
}