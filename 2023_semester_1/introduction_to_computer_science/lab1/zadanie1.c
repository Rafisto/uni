#include <stdio.h>

char message[] = "ABRAKADABRA";
int message_length = sizeof(message) - 1; // subtract null terminator

int main(void)
{
    for (int i = 0; i < message_length; i++)
    {
        for (int k = 0; k < i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < message_length - i; j++)
        {
            printf("%c ", message[j]);
        }
        printf("\n");
    }
    return 0;
}
