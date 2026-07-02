#include "Wheels.h"

Wheels w;
volatile char cmd;

// (int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
// 7 8 5 12 11 10

// white - EN A - SPEED R - PIN 5
// gray - IN1 - PIN 11
// purple - IN2 - PIN 12
// blue - IN3 - PIN 8
// green - IN4 - PIN 7
// yellow - EN B - SPEED L - PIN 10

void setup() {
  w.attach(7,8,5,12,11,10);
}

void loop() {
  w.goForward(10);
  delay(2000);
  w.goBack(10);
  delay(2000);
}
