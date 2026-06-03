#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "Wheels.h"

#define SPEED 200
#define BT_INTERVAL 100
#define PING_INTERVAL 50
#define SERVO_MOVE_TIME 600
#define SWEEP_INTERVAL 200
#define BACKTRACK_TIME 1500

Wheels w;
Servo srv;
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Unified Encoder Variables with Direction Modifiers
volatile int raw_cnt0 = 0;  
volatile int raw_cnt1 = 0;
long total_cnt0 = 0, total_cnt1 = 0;  

int dirL = 0;  
int dirR = 0;
unsigned long lastBTTime = 0;
unsigned long lastLCDTime = 0;

// Scanner and Timing Variables
unsigned long lastPingTime = 0;
unsigned long stateStartTime = 0;
unsigned long lastSweepTime = 0;
int sweepIndex = 0;
int sweepAngles[] = {45, 90, 135, 90};

float distance;
float d[] = {0, 0, 0};
float dFarLeft, dLeft, dCenter, dRight, dFarRight;
int current_angle = 90;

// State Machine for Autonomous Map Generation
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
State state = FORWARD;

// HC-SR04 Pin Mapping
#define ECHO_PIN A2
#define TRIG_PIN 4

// L298N Motor Driver Pinout
#define MOTOR_ENA 6   
#define MOTOR_ENB 5   
#define MOTOR_IN1 11  
#define MOTOR_IN2 12  
#define MOTOR_IN3 8   
#define MOTOR_IN4 7   

void setup_motor() {
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_ENB, OUTPUT);
  w.attach(MOTOR_IN4, MOTOR_IN3, MOTOR_ENB, MOTOR_IN2, MOTOR_IN1, MOTOR_ENA);
}

void moveRobot(int l, int r, void (Wheels::*m)()) {
  dirL = l;
  dirR = r;
  (w.*m)();
  w.setSpeed(SPEED);
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
  if (millis() - lastBTTime > BT_INTERVAL) {
    Serial.print("L:");
    Serial.print(total_cnt0);
    Serial.print(",R:");
    Serial.println(total_cnt1);
    lastBTTime = millis();
  }
}

void updateLCD() {
  if (millis() - lastLCDTime > 200) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:"); lcd.print(total_cnt0);
    lcd.setCursor(9, 0);
    lcd.print("R:"); lcd.print(total_cnt1);

    lcd.setCursor(0, 1);
    lcd.print("d="); lcd.print(distance);
    lcd.setCursor(9, 1);

    switch (state) {
      case FORWARD:   lcd.print("FWD"); break;
      case SCAN_FL:   lcd.print("SFL"); break;
      case SCAN_L:    lcd.print("S_L"); break;
      case SCAN_C:    lcd.print("S_C"); break;
      case SCAN_R:    lcd.print("S_R"); break;
      case SCAN_FR:   lcd.print("SFR"); break;
      case BACKTRACK: lcd.print("TRN"); break;
      default:        lcd.print("---"); break;
    }
    lcd.print(" A:");
    lcd.print(current_angle - 90);
    lastLCDTime = millis();
  }
}

void handleActiveForward() {
  unsigned long now = millis();

  if (now - lastSweepTime > SWEEP_INTERVAL) {
    sweepIndex = (sweepIndex + 1) % 4;
    current_angle = sweepAngles[sweepIndex];
    srv.write(current_angle);
    lastSweepTime = now;
  }

  if (now - lastPingTime > PING_INTERVAL) {
    distance = getDistance();
    lastPingTime = now;

    if (distance > 5 && distance < 30) {
      moveRobot(0, 0, &Wheels::stop);
      state = STOPPED; 
    } else {
      moveRobot(1, 1, &Wheels::forward);
    }
  }
}

void evaluatePath() {
  // Free routing rules based on spatial clearance profiles
  if (dFarRight > 40 && dRight > 30) {
    moveRobot(-1, 1, &Wheels::backLeft); // Tank turn right or complex forwardRight
  } else if (dFarLeft > 40 && dLeft > 30) {
    moveRobot(1, -1, &Wheels::backRight);
  } else if (dRight >= dLeft) {
    moveRobot(-1, 1, &Wheels::backLeft);
  } else if (dLeft > dRight) {
    moveRobot(1, -1, &Wheels::backRight);
  } else {
    moveRobot(-1, -1, &Wheels::back);
  }
}

void runScanner() {
  unsigned long now = millis();

  switch (state) {
    case STOPPED:
      current_angle = 170;
      srv.write(current_angle);
      stateStartTime = now;
      state = SCAN_FL;
      break;

    case SCAN_FL:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dFarLeft = getDistance();
        current_angle = 130;
        srv.write(current_angle);
        stateStartTime = now;
        state = SCAN_L;
      }
      break;

    case SCAN_L:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dLeft = getDistance();
        current_angle = 90;
        srv.write(current_angle);
        stateStartTime = now;
        state = SCAN_C;
      }
      break;

    case SCAN_C:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dCenter = getDistance();
        current_angle = 50;
        srv.write(current_angle);
        stateStartTime = now;
        state = SCAN_R;
      }
      break;

    case SCAN_R:
      if (now - stateStartTime > SERVO_MOVE_TIME) {
        dRight = getDistance();
        current_angle = 10;
        srv.write(current_angle);
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
      current_angle = 90;
      break;

    case BACKTRACK:
      if (now - stateStartTime > BACKTRACK_TIME) {
        moveRobot(0, 0, &Wheels::stop);
        current_angle = 90;
        srv.write(current_angle);
        delay(300);
        stateStartTime = now;
        state = FORWARD;
      }
      break;
  }
}

void setup() {
  setup_motor();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  srv.attach(3);
  srv.write(90);

  Serial.begin(9600);
  for (int i = 0; i < 5; ++i) {
    Serial.println("reset");
    delay(50);
  }

  // Pin Change Interrupt Config for Port C (A0, A1 Encoders)
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9);
}

void loop() {
  processCounts();
  sendBTData(); // Feeds your real-time Python file-watcher tracking script
  updateLCD();

  if (state == FORWARD) {
    handleActiveForward();
  } else {
    runScanner();
  }
}

// Fixed, clean interrupt-driven counter logic
volatile uint8_t last_PINC = 0;

ISR(PCINT1_vect) {
  uint8_t current_PINC = PINC;
  uint8_t changed = current_PINC ^ last_PINC;
  last_PINC = current_PINC;

  if ((changed & (1 << PC0)) && (current_PINC & (1 << PC0))) raw_cnt0++;
  if ((changed & (1 << PC1)) && (current_PINC & (1 << PC1))) raw_cnt1++;
}