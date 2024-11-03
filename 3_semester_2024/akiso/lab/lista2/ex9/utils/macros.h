/*
    Rafał Włodarczyk
    Macros for printing information and failing the program.
*/

#ifndef UTILS_MACROS_H
#define UTILS_MACROS_H

#include <stdio.h>
#include <stdlib.h>

#define rinfo(fmt, ...) printf("(%s:%d in %s): " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define rfail(fmt, ...)                                                                  \
    {                                                                                    \
        printf("(%s:%d in %s): " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        exit(EXIT_FAILURE);                                                              \
    }

#endif // UTILS_MACROS_H