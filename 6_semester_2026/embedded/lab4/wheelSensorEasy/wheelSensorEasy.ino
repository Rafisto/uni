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

 attachPCINT(digitalPinToPCINT(INTINPUT0), increment, CHANGE);
 attachPCINT(digitalPinToPCINT(INTINPUT1), increment, CHANGE);
}

void loop() {
  Serial.print(cnt0);
  Serial.println(cnt1);
  delay(250);
}

void increment() {
  if(digitalRead(INTINPUT0))
    cnt0++;
  else if(digitalRead(INTINPUT1))
    cnt1++;
}
