#include <Servo.h>
#include "Wheels.h"

#define SPEED 200
#define PING_INTERVAL 50
#define SERVO_MOVE_TIME 800
#define SWEEP_INTERVAL 200
#define BACKTRACK_TIME 2000

#define ECHO_PIN A2
#define TRIG_PIN 4

void setup_ultrasonic_sensor() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

Wheels w;
Servo srv;

// Global counters and direction multipliers
volatile int raw_cnt0 = 0;  // Raw ticks from ISR
volatile int raw_cnt1 = 0;
int last_raw0 = 0, last_raw1 = 0;
long total_cnt0 = 0, total_cnt1 = 0;  // Processed signed counts

int dirL = 0;  // -1, 0, or 1
int dirR = 0;

unsigned long lastPingTime = 0;
unsigned long stateStartTime = 0;
unsigned long lastSweepTime = 0;
unsigned long lastBTTime = 0;

int sweepIndex = 0;
int sweepAngles[] = { 45, 90, 135, 90 };
float distance;
float d[] = { 0, 0, 0 };
float dFarLeft, dLeft, dCenter, dRight, dFarRight;

enum State { FORWARD,
             STOPPED,
             SCAN_FL,
             SCAN_L,
             SCAN_C,
             SCAN_R,
             SCAN_FR,
             DECIDE,
             BACKTRACK };
State state;
int angle;

// --- Helper to set motor state and directions ---
void moveRobot(int l, int r, void (Wheels::*m)()) {
  dirL = l;
  dirR = r;
  (w.*m)();
  w.setSpeed(SPEED);
}

// l289n Pinout
#define MOTOR_ENA 6   // white - EN A - SPEED R - PIN 6
#define MOTOR_ENB 5   // yellow - EN B - SPEED L - PIN 5
#define MOTOR_IN1 11  // gray - IN1 - PIN 11
#define MOTOR_IN2 12  // purple - IN2 - PIN 12
#define MOTOR_IN3 8   // blue - IN3 - PIN 8
#define MOTOR_IN4 7   // green - IN4 - PIN 7
void setup_motor() {
  pinMode(6, MOTOR_ENA);
  pinMode(5, MOTOR_ENB);
  w.attach(MOTOR_IN4, MOTOR_IN3, MOTOR_ENB, MOTOR_IN2, MOTOR_IN1, MOTOR_ENA);
}

#define SDA_PIN A4
#define SCL_PIN A5
// void setup_lcd() {
//   lcd.init();
//   lcd.backlight();
//   lcd.setCursor(0, 0);
// }

#define SERVO_PIN 3
void setup_servo() {
  srv.attach(SERVO_PIN);
  angle = 90;
  srv.write(90);
}

void setup() {
  setup_ultrasonic_sensor();
  setup_motor();
  setup_servo();

  Serial.begin(9600);

  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9);

  state = FORWARD;
}

void processCounts() {
  noInterrupts();
  int t0 = raw_cnt0;
  int t1 = raw_cnt1;
  raw_cnt0 = 0;
  raw_cnt1 = 0;
  interrupts();

  total_cnt0 += (t0 * dirL);
  total_cnt1 += (t1 * dirR);
}

void sendBTData() {
  if (millis() - lastBTTime > 100) {
    Serial.print("L:");
    Serial.print(total_cnt0);
    Serial.print(",R:");
    Serial.println(total_cnt1);
    lastBTTime = millis();
  }
}

void handleActiveForward() {
  unsigned long now = millis();
  if (now - lastSweepTime > SWEEP_INTERVAL) {
    sweepIndex = (sweepIndex + 1) % 4;
    angle = sweepAngles[sweepIndex];
    srv.write(angle);
    lastSweepTime = now;
  }

  if (now - lastPingTime > PING_INTERVAL) {
    distance = getDistance();
    lastPingTime = now;
    if (distance > 0 && distance < 25) {
      moveRobot(0, 0, &Wheels::stop);
      state = STOPPED;
    } else {
      moveRobot(1, 1, &Wheels::forward);
    }
  }
}

void evaluatePath() {
  // 2 options
  if (dRight >= dLeft) {
    moveRobot(0, 1, &Wheels::forwardRight);
  } else {
    moveRobot(1, 0, &Wheels::forwardLeft);
  }
  // if (dFarRight > 40 && dRight > 30) {
  //   moveRobot(1, -1, &Wheels::forwardRight);
  // } else if (dFarLeft > 40 && dLeft > 30) {
  //   moveRobot(-1, 1, &Wheels::forwardLeft);
  // } else if (dRight >= dLeft) {
  //   moveRobot(1, -1, &Wheels::forwardRight);
  // } else {
  //   moveRobot(-1, 1, &Wheels::forwardLeft);
  // }
}



float getDistance() {
  for (int i = 0; i < 3; ++i) {
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
  else if ((d[1] < d[0]) ^ (d[1] < d[2])) best = d[1];
  else best = d[2];
  return (best * 0.0343 / 2);
}


void runScanner() {
  unsigned long now = millis();
  switch (state) {
    case STOPPED:
      srv.write(170);
      stateStartTime = now;
      state = SCAN_FL;
      break;

    case SCAN_FL:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dFarLeft = getDistance();
        angle = 130;
        srv.write(130);
        stateStartTime = now;
        state = SCAN_L;
      }
      break;

    case SCAN_L:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dLeft = getDistance();
        angle = 90;
        srv.write(90);
        stateStartTime = now;
        state = SCAN_C;
      }
      break;

    case SCAN_C:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dCenter = getDistance();
        angle = 50;
        srv.write(50);
        stateStartTime = now;
        state = SCAN_R;
      }
      break;

    case SCAN_R:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dRight = getDistance();
        angle = 10;
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
        moveRobot(0, 0, &Wheels::stop);

        angle = 90;
        srv.write(90);
        delay(500);

        stateStartTime = now;
        state = FORWARD;
      }
      break;
  }
}


void loop() {
  processCounts();
  sendBTData();

  if (state == FORWARD) handleActiveForward();
  else runScanner();
}

ISR(PCINT1_vect) {
  if (PINC & (1 << PC0)) raw_cnt0++;
  if (PINC & (1 << PC1)) raw_cnt1++;
}