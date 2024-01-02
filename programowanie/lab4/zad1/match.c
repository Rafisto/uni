// Zadanie 1, match.c Rafał Włodarczyk

#include <stdbool.h>

bool match(char* pattern, char* text) {
    // null terminator approach
    if (*pattern == '\0' && *text == '\0') return true;
    if (*pattern == '\0' || *text == '\0') return false;
    if (*pattern == *text) return match(pattern + 1, text + 1);
    if (*pattern == '?') return match(pattern + 1, text + 1);
    if (*pattern == '*') return match(pattern + 1, text) || match(pattern, text + 1);
    return false;
}
