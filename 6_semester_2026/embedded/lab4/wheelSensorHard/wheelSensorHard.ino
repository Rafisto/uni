#include "Wheels.h"

#include "PinChangeInterrupt.h"

#define INTINPUT0 A0
#define INTINPUT1 A1

Wheels w;
volatile int cnt0, cnt1;

void setup() {
  w.attach(8,7,11,5,4,10);
  w.setSpeed(80);

  w.forward();

  Serial.begin(9600);

  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  cnt0=0;
  cnt1=0;

  PCICR  = 0x02;  // włącz pin change interrupt dla 1 grupy (A0..A5)
  PCMSK1 = 0x03;  // włącz przerwanie dla A0, A1
}

void loop() {
  Serial.print(cnt0);
  Serial.print(" ");
  Serial.println(cnt1);
  delay(250);
}

ISR(PCINT1_vect) {
  if(digitalRead(INTINPUT0))
    cnt0++;
  else if(digitalRead(INTINPUT1))
    cnt1++;
}
