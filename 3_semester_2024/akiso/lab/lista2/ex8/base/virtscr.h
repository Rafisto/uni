#ifndef BASE_VIRSCR
#define BASE_VIRSCR

#include "scr.h"

char VIRTUAL_SCREEN[80][512][2];
unsigned int VIRTUAL_SCREEN_CURSOR_X = 0;
unsigned int VIRTUAL_SCREEN_CURSOR_Y = 0;
unsigned int VIRTUAL_SCREEN_SCROLL = 0;

void display()
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            scr_write_at(i, j, VIRTUAL_SCREEN[j][VIRTUAL_SCREEN_SCROLL + i][0], VIRTUAL_SCREEN[j][VIRTUAL_SCREEN_SCROLL + i][1]);
        }
    }
}

void scroll_down()
{
    if (VIRTUAL_SCREEN_SCROLL == 511)
    {
        return;
    }

    VIRTUAL_SCREEN_SCROLL++;
    display();
}

void scroll_up()
{
    if (VIRTUAL_SCREEN_SCROLL == 0)
    {
        return;
    }

    VIRTUAL_SCREEN_SCROLL--;
    display();
}

void write_char(char character, int color)
{
    if (character == '\n')
    {
        VIRTUAL_SCREEN_CURSOR_X = 0;
        VIRTUAL_SCREEN_CURSOR_Y++;
    }
    else
    {
        VIRTUAL_SCREEN[VIRTUAL_SCREEN_CURSOR_X][VIRTUAL_SCREEN_CURSOR_Y][0] = character;
        VIRTUAL_SCREEN[VIRTUAL_SCREEN_CURSOR_X][VIRTUAL_SCREEN_CURSOR_Y][1] = color;
        VIRTUAL_SCREEN_CURSOR_X++;
    }

    if (VIRTUAL_SCREEN_CURSOR_X >= 80)
    {
        VIRTUAL_SCREEN_CURSOR_X = 0;
        VIRTUAL_SCREEN_CURSOR_Y++;
    }

    if (VIRTUAL_SCREEN_CURSOR_Y >= 511)
    {
        scroll_up();
        VIRTUAL_SCREEN_CURSOR_Y--;
    }

    display();
}

void write_string(char *string, int color)
{
    int i = 0;

    while (string[i] != '\0')
    {
        write_char(string[i], color);
        i++;
    }
}

#endif // BASE_VIRSCR
