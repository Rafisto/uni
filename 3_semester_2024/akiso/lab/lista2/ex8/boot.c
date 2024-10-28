#include "base/kbd.h"
#include "base/scr.h"
#include "base/virtscr.h"

#include "base/itoa.h"

void main() {
    char *video_memory = (char*) 0xB8000;
    char *message = "Hello World!\n";
    
    scr_clear();

    write_string("Welcome to the virtual 80x512 screen!\n", 0x0F);
    write_string("Use 'j' to scroll down and 'k' to scroll up\n", 0x0F);
    for (int i = 0; i < 256; i++)
    {
        write_string(itoa(i), i);
        write_string(" ", i);
        write_string(message, i);
    }
   
    while(1) {
        char scancode = read_char();
        if (scancode == 'j') {
            scroll_down();
        } else if (scancode == 'k') {
            scroll_up();
        }
    }
}
