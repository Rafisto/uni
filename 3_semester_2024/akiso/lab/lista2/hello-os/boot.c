// boot.c

void main() {
    char *video_memory = (char*) 0xB8000;
    char *message = "Hello World!";
    
    unsigned char background_colors[] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70}; 
    unsigned char font_colors[] = {0x0F, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x09, 0x02};
    int bg_count = sizeof(background_colors) / sizeof(background_colors[0]);
    int font_count = sizeof(font_colors) / sizeof(font_colors[0]);
    
    int line = 0;

    for (int i = 0; i < bg_count; i++) {
        for (int j = 0; j < font_count; j++) {
            for (int k = 0; message[k] != '\0'; k++) {
                int index = (line * 80 + k) * 2; 
                video_memory[index] = message[k];
                video_memory[index + 1] = background_colors[i] | font_colors[j]; 
            }
            line++;
        }
    }

    while(1);
}
