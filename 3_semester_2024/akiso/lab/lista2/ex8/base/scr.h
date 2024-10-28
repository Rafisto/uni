#ifndef BASE_SCR
#define BASE_SCR

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

void scr_clear()
{
    char *video_memory = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_SIZE; i += 2)
    {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x00;
    }
}

void scr_write_at(int row, int column, char character, int color)
{
    char *video_memory = (char *)VIDEO_MEMORY;

    if (row >= 0 && row < SCREEN_HEIGHT && column >= 0 && column < SCREEN_WIDTH)
    {
        int position = (row * SCREEN_WIDTH + column) * 2;
        video_memory[position] = character;
        video_memory[position + 1] = color;
    }
}

#endif // BASE_SCR
