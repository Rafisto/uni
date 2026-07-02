// https://playground.arduino.cc/code/timer1
// Jeśli nie masz tej biblioteki, wybierz:
// Narzędzia->Zarządzaj bibliotekami, w oknie wyszukaj 
// bibliotekę TimerOne i zanistaluj.
//
#include "TimerOne.h"

// pin, na którym obserwujemy działanie
// pin 13 to dioda LED, ale możesz podłączyć też głośnik
#define BEEPER 13

// wstępny okres w milisekundach
long int intPeriod = 500000;

void setup() {
  pinMode(BEEPER, OUTPUT);
  Timer1.initialize();
  TimerUpdate();

  Serial.begin(9600);

}

// główna pętla
void loop() {
  while(Serial.available()){
    char i = Serial.read();
    switch(i) {
      case '+' : intPeriod += 100000; TimerUpdate(); break;
      case '-' : intPeriod -= 100000; TimerUpdate(); break;
    }
    Serial.println(intPeriod);
  }

}

// aktualizuje Timer1 aktualną wartością intPeriod
void TimerUpdate() {
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(doBeep, intPeriod);
}

// zmienia wartość pinu BEEPER
void doBeep() {
  digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}
