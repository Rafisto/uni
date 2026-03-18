#include "Wheels.h"

Wheels w;
volatile char cmd;

void setup() {
  w.attach(7,8,5,12,11,10);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'f': {
        int cm = (int)Serial.parseInt();
        if (cm > 0) w.goForward(cm);
        break;
      }
      case 'b': {
        int cm = (int)Serial.parseInt();
        if (cm > 0) w.goBack(cm);
        break;
      }
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
}
