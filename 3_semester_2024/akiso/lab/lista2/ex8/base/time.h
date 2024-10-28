#ifndef BASE_TIME
#define BASE_TIME

void sleep(unsigned int milliseconds) {
    volatile unsigned int count;
    while (milliseconds > 0) {
        for (count = 0; count < 100000; count++) {
            // Busy-wait loop
        }
        milliseconds--;
    }
}

#endif // BASE_TIME
