#include <stdio.h>
#include <signal.h>

int main() {
    int pid;
    printf("Enter the PID of the process you want to kill: ");
    scanf("%d", &pid);
    kill(pid, SIGKILL);
    return 0;
}