// Zadanie 4, newagent.c Rafał Włodarczyk

#include "agents.h"

struct agent newagent(int x, int y) {
    struct agent a;
    a.x = x;
    a.y = y;
    return a;
}
