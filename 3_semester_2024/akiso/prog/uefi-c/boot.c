#include "base/keyboard.h"
#include "base/screen.h"

void main() {
    char *message = "Rafist0 is reading your input";

    clear();
    write_string(message);

    while(1) {
        char input = read_char();
        clear();
        write_char(input);
    }
}
