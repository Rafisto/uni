#include "base/keyboard.c"
#include "base/screen.c"
#include "base/shutdown.c"

int main(void)
{
    char *message = "I am echoing your input, type 'exit' to shutdown";

    clear();
    write_string_at(message, 0, 0);

    int buffer_index = 0;
    char buffer[80];

    int current_row = 1;
    int current_column = 2;

    write_at('>', current_row, 0);

    while (1)
    {
        char input = read_char();

        if (input == '\n')
        {
            current_row++;

            if (buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'i' && buffer[3] == 't')
            {
                shutdown();
            }

            buffer[buffer_index] = '\0';
            write_string_at(buffer, current_row, 0);
            buffer_index = 0;
            current_row++;

            current_column = 2;
            write_at('>', current_row, 0);

            continue;
        }
        else
        {
            buffer[buffer_index] = input;
            buffer_index += 1;
        }

        write_at(input, current_row, current_column);

        current_column++;

        if (current_column >= SCREEN_WIDTH)
        {
            current_column = 0;
            current_row++;
        }
    }
}
