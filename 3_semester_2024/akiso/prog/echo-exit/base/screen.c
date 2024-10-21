#define VIDEO_MEMORY 0xB8000
#define SCREEN_COLOR 0x02
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

void clear()
{
    char *video_memory = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_SIZE; i += 2)
    {
        video_memory[i] = ' '; 
        video_memory[i + 1] = 0x00;
    }
}

void write_at(char character, int row, int column)
{
    char *video_memory = (char *)VIDEO_MEMORY;

    if (row >= 0 && row < SCREEN_HEIGHT && column >= 0 && column < SCREEN_WIDTH)
    {
        int position = (row * SCREEN_WIDTH + column) * 2;
        video_memory[position] = character;
        video_memory[position + 1] = SCREEN_COLOR;
    }
}

void write_string_at(char *string, int row, int column)
{
    char *video_memory = (char *)VIDEO_MEMORY;
    int i = 0;

    while (string[i] != '\0' && row < SCREEN_HEIGHT)
    {
        int position = (row * SCREEN_WIDTH + column) * 2;

        video_memory[position] = string[i];
        video_memory[position + 1] = SCREEN_COLOR;
        column++;

        if (column >= SCREEN_WIDTH)
        {
            column = 0;
            row++;
        }
        i++;
    }
}