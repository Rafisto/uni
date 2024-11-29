#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int sig) {
    printf("Signal received: %d (%s)\n", sig, strsignal(sig));
}

int main() {
    printf("PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);

    while (1) {}

    return 0;
}