// Zadanie 2, functions.h Rafał Włodarczyk

typedef struct
{
    int red;
    int white;
} Result;

int main(void);
Result check_code(int *guess);
Result check(int guess[], int code[]);

int guess(void);
