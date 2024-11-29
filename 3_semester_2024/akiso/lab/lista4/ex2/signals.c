#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int sig) {
    printf("Signal received: %d (%s)\n", sig, strsignal(sig));
}

int main() {
    struct sigaction sa;
    int rc;

    sa.sa_handler = signal_handler; // set the handler
    sigemptyset(&sa.sa_mask); // clean signal mask
    sa.sa_flags = 0; // no additional flags

    for (int i = 1; i < NSIG; i++) {
        rc = sigaction(i, &sa, NULL);
        if (rc == -1) {
            fprintf(stderr, "[-] Unable to register handler for the signal %d (%s)\n", i, strsignal(i));
        } else {
            printf("[+] Handler registered for the signal %d (%s)\n", i, strsignal(i));
        }
    }

    return 0;
}