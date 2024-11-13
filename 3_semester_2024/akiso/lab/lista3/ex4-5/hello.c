#include "types.h"
#include "stat.h"
#include "user.h"

void print_rainbow()
{
    char escape_code[3];
    char *text = "Hello, world!\n";

    for (int i = 0; i < 256; i++)
    {
        escape_code[0] = 0x1B;
        escape_code[1] = i;
        escape_code[2] = '\0';

        write(1, escape_code, 3);
        write(1, text, 14);
    }
}

int main(int argc, char *argv[])
{
    print_rainbow();

    char ret_code[3];
    ret_code[0] = 0x1B;
    ret_code[1] = 7;
    ret_code[2] = '\0';
    write(1, ret_code, 3);
    exit();
}
