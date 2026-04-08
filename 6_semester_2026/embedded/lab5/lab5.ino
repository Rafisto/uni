#include <Servo.h>

#include "Ticker.h"
#include "Wheels.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <TimerOne.h>

Wheels w;
volatile char cmd;

// (int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
// 7 8 5 12 11 10

// l289n Pinout
// white - EN A - SPEED R - PIN 6
// gray - IN1 - PIN 11
// purple - IN2 - PIN 12
// blue - IN3 - PIN 8
// green - IN4 - PIN 7
// yellow - EN B - SPEED L - PIN 5

// LiqidCrystal_I2C
// SDA - A4
// SCL - A5

// ROW 1 - Distance to Go
// ROW 2 - Animation
// - First 2: Motor L (F/B/S)
// - Last 2 : Motor R (F/B/S)

// HC-SR04
// ECHO - receives
// TRIG - sends
const int echoPin = A2;
const int trigPin = 4;
float duration, distance;

// SERVO PIN 2
const int servoPin = 3;

// INTERRUPTS
// A0 - LEFT FRONT WHEEL - PCINT8
// A1 - RIGHT FRONT WHEEL - PCINT9
#define INTINPUT0 A0
#define INTINPUT1 A1
volatile int cnt0, cnt1;

// TIMER BEEP
// #define REVERSE_PIN 10
// long int intPeriod = 100000;

LiquidCrystal_I2C lcd(0x27, 20, 4);

// enum Direction { FORWARD, BACKWARD, STOP };

// Direction left = STOP;
// Direction right = STOP;

enum State {
  FORWARD,
  BACKTRACK_LEFT,
  BACKTRACK_RIGHT,
  BACKTRACK_BACK,
};

State state = FORWARD;

// #define fn_move_refresh 100
// #define fn_display_refresh 200

// 255 x 20 = 10cm
// RATE at 255 = 10cm / 20ms = 1 / 2;

// void fn_move() {
//   if (current < goal) {
//     left = FORWARD;
//     right = FORWARD;
//     w.forward();
//     w.setSpeed(255);
//     current += 5;
//   } else {
//     left = STOP;
//     right = STOP;
//     w.stop();
//   }
// }

void fn_display_isr() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(cnt0);

  lcd.setCursor(4, 0);
  lcd.print("R");
  lcd.print(cnt1);

  lcd.setCursor(0, 1);
  lcd.print("d=");
  lcd.print(distance);

  lcd.setCursor(14, 1);
  switch (state) {
  case FORWARD: {
    lcd.print("F");
    break;
  }
  case BACKTRACK_LEFT: {
    lcd.print("BL");
    break;
  }
  case BACKTRACK_RIGHT: {
    lcd.print("BR");
    break;
  }
  case BACKTRACK_BACK: {
    lcd.print("BB");
    break;
  }
  }
}

// Ticker move(fn_move_refresh, fn_move);
// Ticker display(fn_display_refresh, fn_display);

Servo srv;

void setup() {
  // HC-SR04
  // https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo
  srv.attach(servoPin);
  srv.write(90);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  w.attach(7, 8, 5, 12, 11, 6);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  cnt0 = 0;
  cnt1 = 0;

  PCICR = 0x02;
  PCMSK1 = 0x03;

  state = FORWARD;
}

void dist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
}

void select_backtrack() {
  // rot 30 left measure
  double l_dist;
  srv.write(150);
  delay(1000);
  dist();
  l_dist = distance;

  // rot 30 right measure
  double r_dist;
  srv.write(30);
  delay(1000);
  dist();
  r_dist = distance;

  srv.write(90);
  if (r_dist && l_dist < 30) {
    state = BACKTRACK_BACK;
  } else if (r_dist > l_dist) {
    state = BACKTRACK_LEFT;
  } else {
    state = BACKTRACK_RIGHT;
  }
}

#define SPEED 150
#define DELAY_BASE 1000

void loop() {
  fn_display_isr();
  switch (state) {
  case FORWARD: {
    w.forward();
    w.setSpeed(SPEED);
    delay(200);
    dist();
    if (distance < 30) {
      w.stop();
      select_backtrack();
    }
  } break;
  case BACKTRACK_RIGHT: {
    w.back();
    delay(DELAY_BASE);
    w.forwardRight();
    w.backLeft();
    w.setSpeed(SPEED);
    delay(DELAY_BASE);
    w.stop();
    state = FORWARD;
  } break;
  case BACKTRACK_LEFT: {
    w.back();
    delay(DELAY_BASE);
    w.forwardLeft();
    w.backRight();
    w.setSpeed(SPEED);
    delay(DELAY_BASE);
    w.stop();
    state = FORWARD;
  } break;
  case BACKTRACK_BACK: {
    w.back();
    delay(1000);
    w.setSpeed(SPEED);
    w.stop();
    state = FORWARD;
  } break;
  }
}

ISR(PCINT1_vect) {
  cnt0 += PINC & (1 << PC0) >> PC0 & 1;
  cnt1 += PINC & (1 << PC1) >> PC1 & 1;
}