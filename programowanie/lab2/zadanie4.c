// Zadanie 4, zadanie4.c Rafał Włodarczyk
#include <stdio.h>
#include <time.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysTillDate(int day, int month, int year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = day - 1;

    for (int i = 0; i < month-1; i++) {
        days += daysInMonth[i];
    }

    for (int i = 1; i < year; i++) {
        days += 365 + isLeapYear(i);
    }

    if (isLeapYear(year) && month > 2) {
        days += 1;
    }

    return days;
}

int main(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int days = daysTillDate(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) - daysTillDate(27, 9, 2004);
    int seconds = days * 24 * 3600;
    printf("Days since 27.09.2004 %d\n", days);
    printf("Seconds since 27.09.2004 %d\n", seconds);
    return 0;
}
