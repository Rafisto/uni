// Zadanie 1, match.c Rafał Włodarczyk

#include <stdbool.h>

bool match(char* pattern, char* text) {
    // null terminator approach
    if (*pattern == '*')
    {
        if(*text != '\0') return match(pattern + 1, text) || match(pattern, text + 1);
        else return match(pattern + 1, text);
    }
    else if (*pattern == '\0' && *text == '\0') return true;
    else if (*pattern == '\0' || *text == '\0') return false;
    else if (*pattern == *text) return match(pattern + 1, text + 1);
    else if (*pattern == '?') return match(pattern + 1, text + 1);
    return false;
}
