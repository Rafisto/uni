// Zadanie 1, main.c Rafał Włodarczyk

#include <stdio.h>
#include "functions.h"

struct test_case
{
    char *pattern;
    char *text;
    bool expected;
};

struct test_case tests[] = {
    {"*", "", true},
    {"a*", "aaaaaa", true},
    {"a*a", "aaaaaab", false},
    {"*.doc", "document.doc", true},
    {"*.doc", "document.docx", false},
    {"*.doc", "document.do", false},
    {"*.doc", ".doc", true},
    {"a???", "aaaa", true},
    {"a???", "abcd", true},
    {"a???", "abc", false},
    {"a???", "abcde", false},
    {"b?ba", "baab", false},
    {"a??a", "abba", true},
    {"a*b*b*c", "aababc", true},
    {"a*b*b*c", "aaaac", false},
    {"a*b*b*c", "abaaac", false},
    {"a*b*a", "abababababababababababa", true},
    {"a*b*a", "ababababababababababab", false},
};

int main(void)
{
    for (unsigned long i = 0; i < sizeof(tests) / sizeof(struct test_case); i++)
    {
        struct test_case test = tests[i];
        char *pattern = test.pattern;
        char *text = test.text;
        bool result = match(test.pattern, test.text);
        if (result != test.expected)
        {
            printf("Test %lu failed %d != %d (pattern '%s'; case '%s')\n", i, result, test.expected, pattern, text);
        }
        printf("Test %lu passed (pattern '%s'; case '%s')\n", i, pattern, text);
    }
}
