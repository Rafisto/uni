#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#include "Ticker.h"
#include "Wheels.h"

#include "eepromlib.hpp"

#define SPEED 200
#define DELAY_BASE 1000
#define PING_INTERVAL 50
#define SERVO_MOVE_TIME 800
#define SWEEP_INTERVAL 200
#define BACKTRACK_TIME 2000

Wheels w;
Servo srv;
LiquidCrystal_I2C lcd(0x27, 20, 4);
int e_left = 1;
int e_right = 1;
int e_id = 0;

#define INTINPUT0 A0
#define INTINPUT1 A1
volatile int cnt0, cnt1;

unsigned long lastPingTime = 0;
unsigned long stateStartTime = 0;
unsigned long lastSweepTime = 0;
int sweepIndex = 0;
int sweepAngles[] = {45, 90, 135, 90};

float duration, distance;
float d[] = {0,0,0};
float dFarLeft, dLeft, dCenter, dRight, dFarRight;

enum State {
  FORWARD,
  STOPPED,
  SCAN_FL,
  SCAN_L,
  SCAN_C,
  SCAN_R,
  SCAN_FR,
  DECIDE,
  BACKTRACK
};

State state;
int angle;

void fn_display_isr() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(cnt0);

  lcd.setCursor(8, 0);
  lcd.print("R");
  lcd.print(cnt1);

  lcd.setCursor(0, 1);
  lcd.print("d=");
  lcd.print(distance);

  lcd.setCursor(9,1);

  switch (state) {
    case FORWARD:      lcd.print("FWD"); break;
    case SCAN_FL:      lcd.print("SFL"); break;
    case SCAN_L:       lcd.print("SCL 130"); break;
    case SCAN_C:       lcd.print("SCC 90"); break;
    case SCAN_R:       lcd.print("SCR 50"); break;
    case SCAN_FR:      lcd.print("SFR 10"); break;
    case BACKTRACK:    lcd.print("TRN"); break;
    default:           lcd.print("---"); break;
  }
  
  lcd.print(" ");
  lcd.print(angle-90);
}

// HC-SR04
// ECHO (A2) - receives
// TRIG (4) - sends
#define ECHO_PIN A2
#define TRIG_PIN 4

void setup_ultrasonic_sensor() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

// l289n Pinout
#define MOTOR_ENA 6  // white - EN A - SPEED R - PIN 6
#define MOTOR_ENB 5  // yellow - EN B - SPEED L - PIN 5
#define MOTOR_IN1 11 // gray - IN1 - PIN 11
#define MOTOR_IN2 12 // purple - IN2 - PIN 12
#define MOTOR_IN3 8  // blue - IN3 - PIN 8
#define MOTOR_IN4 7  // green - IN4 - PIN 7
void setup_motor() {
  pinMode(6, MOTOR_ENA);
  pinMode(5, MOTOR_ENB);
  w.attach(MOTOR_IN4, MOTOR_IN3, MOTOR_ENB, MOTOR_IN2, MOTOR_IN1, MOTOR_ENA);
}

// LiqidCrystal_I2C 16x2 LCD
#define SDA_PIN A4
#define SCL_PIN A5
void setup_lcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

#define SERVO_PIN 3
void setup_servo() {
  srv.attach(SERVO_PIN);
  angle=90;
  srv.write(90);
}

void setup_gap_counters() {
  cnt0 = 0;
  cnt1 = 0;

  PCICR = 0x02;
  PCMSK1 = 0x03;
}

void clear_eeprom() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

void dump_eeprom() {
  Serial.begin(115200);

  for (int i = 0; i < EEPROM.length(); i++) {
    Serial.print(EEPROM.read(i), HEX);
    Serial.print(" ");
    if ((i + 1) % 16 == 0) Serial.println();
  }
  Serial.println();

  Serial.end();
}

void setup() {
  // clear_eeprom();
  dump_eeprom();

  setup_ultrasonic_sensor();
  setup_motor();
  setup_servo();
  setup_lcd();
  setup_gap_counters();

  state = FORWARD;
}

float getDistance() {
  for(int i = 0; i < 3; ++i ) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    d[i] = duration;
  }

  long best;
  if ((d[0] > d[1]) ^ (d[0] > d[2])) best = d[0];
  else if((d[1] < d[0]) ^ (d[1] < d[2])) best = d[1];
  else best = d[2];
  return (best * 0.0343 / 2);
}

void handleActiveForward() {
  unsigned long now = millis();

  if (now - lastSweepTime > SWEEP_INTERVAL) {
    sweepIndex = (sweepIndex + 1) % 4;
    angle=sweepAngles[sweepIndex];
    srv.write(sweepAngles[sweepIndex]);
    lastSweepTime = now;
  }

  if (now - lastPingTime > PING_INTERVAL) {
    distance = getDistance();
    lastPingTime = now;

    if (distance > 0 && distance < 25) {
      w.stop();
      e_id = ewrite_int(e_id, cnt0);
      e_id = ewrite_int(e_id, cnt1);
      cnt1 = 0;
      cnt0 = 0; 
      state = STOPPED; 
    } else {
      w.forward();
      e_left = 1;
      e_right = 1;
      w.setSpeed(SPEED);
    }
  }
}

void runScanner() {
  unsigned long now = millis();

  lcd.setCursor(0, 1);
  lcd.print("d=eval  ");

  switch (state) {
    case STOPPED:
      srv.write(170);
      stateStartTime = now;
      state = SCAN_FL;
      break;

    case SCAN_FL:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dFarLeft = getDistance();
        angle=130;
        srv.write(130);
        stateStartTime = now;
        state = SCAN_L;
      }
      break;

    case SCAN_L:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dLeft = getDistance();
        angle=90;
        srv.write(90);
        stateStartTime = now;
        state = SCAN_C;
      }
      break;

    case SCAN_C:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dCenter = getDistance();
        angle=50;
        srv.write(50);
        stateStartTime = now;
        state = SCAN_R;
      }
      break;

    case SCAN_R:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dRight = getDistance();
        angle=10;
        srv.write(10);
        stateStartTime = now;
        state = SCAN_FR;
      }
      break;

    case SCAN_FR:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dFarRight = getDistance();
        state = DECIDE;
      }
      break;

    case DECIDE:
      evaluatePath();
      stateStartTime = now;

      state = BACKTRACK;
      angle = 90;
      break;

    case BACKTRACK:
      if (now - stateStartTime > BACKTRACK_TIME) {
        w.stop();

        angle=90;
        srv.write(90);
        delay(500);

        stateStartTime = now;
        state = FORWARD;
      }
      break;
  }
}

void evaluatePath() {
  if (dFarRight > 40 && dRight > 30) {
    e_id = ewrite_int(e_id, 0xF0);
    w.forwardRight();
    w.backLeft();
  } else if (dFarLeft > 40 && dLeft > 30) {
    e_id = ewrite_int(e_id, 0xF1);
    w.forwardLeft();
    w.backRight();
  } else if (dRight >= dLeft) {
    e_id = ewrite_int(e_id, 0xF2);
    w.forwardRight();
    w.backLeft();
  } else if (dLeft > dRight) {
    e_id = ewrite_int(e_id, 0xF3);
    w.forwardLeft();
    w.backRight();
  } else {
    e_id = ewrite_int(e_id, 0xF4);
    w.back();
  }
  w.setSpeed(SPEED);
}

void loop() {
static unsigned long lastLCD = 0;
  if (millis() - lastLCD > 200) {
    fn_display_isr();
    lastLCD = millis();
  }

  if (state == FORWARD) {
    handleActiveForward();
  } else {
    runScanner();
  }
}

ISR(PCINT1_vect) {
  cnt0 += PINC & (1 << PC0) >> PC0 & 1;
  cnt1 += PINC & (1 << PC1) >> PC1 & 1;
}
