#ifndef BASE_ITOA
#define BASE_ITOA

char* itoa(int number) {
    static char buffer[12]; // Enough to hold -2147483648 and null terminator
    char* ptr = buffer + sizeof(buffer) - 1;
    int isNegative = number < 0;
    
    *ptr = '\0';
    
    if (number == 0) {
        *(--ptr) = '0';
    } else {
        unsigned int n = isNegative ? -number : number;
        while (n != 0) {
            *(--ptr) = '0' + (n % 10);
            n /= 10;
        }
        if (isNegative) {
            *(--ptr) = '-';
        }
    }
    
    return ptr;
}

#endif // BASE_ITOA