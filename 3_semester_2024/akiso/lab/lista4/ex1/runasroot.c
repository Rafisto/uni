#include <stdlib.h>
#include <unistd.h>

const char *program = "/bin/bash";

int main() {
    setuid(0); // root
    system(program);
    return 0;
}