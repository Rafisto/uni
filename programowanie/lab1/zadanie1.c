#include <stdio.h>

char message[] = "ABRAKADABRA";
int message_length = sizeof(message) - 1; // -1 to subtract the null terminator

int main(void)
{
    for (int i = 0; i < message_length; i++)
    {
        printf("%*s", i, "");
        for (int j = 0; j < message_length - i; j++)
        {
            printf("%c ", message[j]);
        }
        printf("\n");
    }
    return 0;
}
