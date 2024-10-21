#ifndef BASE_SCREEN
#define BASE_SCREEN

#define VIDEO_MEMORY 0xB8000;
#define SCREEN_COLOR 0x02;
#define SCEREN_SIZE 4000; // 80 * 25 * 2

void clear() {
    char *video_memory = (char*) VIDEO_MEMORY;
    int screen_size = (int) SCEREN_SIZE;
    for (int i = 0; i < screen_size; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x00;
    }
}

void write_char(char character) {
    char *video_memory = (char*) VIDEO_MEMORY;
    int screen_size = (int) SCEREN_SIZE;
    for (int i = 0; i < screen_size; i += 2) {
        if (video_memory[i] == ' ') {
            video_memory[i] = character;
            video_memory[i + 1] = SCREEN_COLOR;
            break;
        }
    }
}

void write_string(char* string) {
    char *video_memory = (char*) VIDEO_MEMORY;
    int screen_size = (int) SCEREN_SIZE;
    int i = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        video_memory[i * 2] = string[i];
        video_memory[i * 2 + 1] = SCREEN_COLOR;
    }
}

#endif