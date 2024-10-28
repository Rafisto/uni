#include <stdio.h>

char *message = "Hello, World!";

int main() {
    // interate through 8 bit 256-color lookup table
    // \x1b[1m - bold text from SGR (Select Graphic Rendition) parameters
    // \x1b[38;5;%dm - set text color
    for (int i = 0; i < 256; i++) {
        printf("\x1b[1m\x1b[38;5;%dm %s\n", i, message);
    }
}

// gcc -Wall -pedantic ansi_colors.c -o ansi_colors && ./ansi_colors