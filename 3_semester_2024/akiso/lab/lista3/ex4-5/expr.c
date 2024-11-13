#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;

  if (argc < 4) {
    printf(2, "Usage: expr <number> <operator> <number>\n");
    exit();
  }

    int a = atoi(argv[1]);
    int b = atoi(argv[3]);
    char *op = argv[2];

    if (strcmp(op, "+") == 0) {
        printf(1, "%d\n", a + b);
    } else if (strcmp(op, "-") == 0) {
        printf(1, "%d\n", a - b);
    } else if (strcmp(op, "*") == 0) {
        printf(1, "%d\n", a * b);
    } else if (strcmp(op, "/") == 0) {
        if (b == 0) {
            printf(2, "Division by zero\n");
            exit();
        }
        printf(1, "%d\n", a / b);
    } else {
        printf(2, "Invalid operator\n");
        exit();
    }

    exit();
}
