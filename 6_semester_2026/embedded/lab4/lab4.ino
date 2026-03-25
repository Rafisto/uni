#include "Wheels.h"
#include "Ticker.h"

Wheels w;
volatile char cmd;

// (int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
// 7 8 5 12 11 10

// l289n Pinout
// white - EN A - SPEED R - PIN 10
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

// INTERRUPTS
// A0 - LEFT FRONT WHEEL - PCINT8
// A1 - RIGHT FRONT WHEEL - PCINT9
#define INTINPUT0 A0
#define INTINPUT1 A1
volatile int cnt0, cnt1;

// TIMER BEEP
#define REVERSE_PIN 9
#define BEEPER 13
long int intPeriod = 100000;

#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

enum Direction {
  FORWARD,
  BACKWARD,
  STOP
};

Direction left = STOP;
Direction right = STOP;

#define fn_move_refresh 100
#define fn_display_refresh 200

int current = 0;
int goal = 100;

// 255 x 20 = 10cm
// RATE at 255 = 10cm / 20ms = 1 / 2;

void fn_move() {
  if (current < goal) {
    left = FORWARD;
    right = FORWARD;
    w.forward();
    w.setSpeed(255);
    current += 5;
  } else {
    left = STOP;
    right = STOP;
    w.stop();
  }
}

// MOVE ANIM
int car_style = 0;

void fn_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(current);
  lcd.setCursor(0, 1);
  switch (left) {
    case FORWARD: lcd.print("LF"); break;
    case BACKWARD: lcd.print("LB"); break;
    case STOP: lcd.print("LS"); break;
  }
  lcd.setCursor(14, 1);
  switch (right) {
    case FORWARD: lcd.print("RF"); break;
    case BACKWARD: lcd.print("RB"); break;
    case STOP: lcd.print("RS"); break;
  }
  if (right != STOP || left != STOP) {
    lcd.setCursor(3, 1);
    switch (car_style) {
      case 0:
        {
          lcd.print("...[____]");
        }
        break;
      case 1:
        {
          lcd.print("...[m___]");
        }
        break;
      case 2:
        {
          lcd.print("...[me__]");
        }
        break;
      case 3:
        {
          lcd.print("...[meo_]");
        }
        break;
      case 4:
        {
          lcd.print("...[meow]");
          car_style = 0;
        }
        break;
    }
    car_style++;
  }
}

void fn_display_isr() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(cnt0);

  lcd.setCursor(0, 1);
  lcd.print("R");
  lcd.print(cnt1);
}

// Ticker move(fn_move_refresh, fn_move);
// Ticker display(fn_display_refresh, fn_display);

void setup() {
  w.attach(7, 8, 5, 12, 11, 10);
  lcd.init();
  lcd.backlight();
  Timer1.initialize();
  Timer1.attachInterrupt(doBeep, intPeriod);
  pinMode(BEEPER,OUTPUT);
  pinMode(REVERSE_PIN,OUTPUT);
  digitalWrite(BEEPER, LOW);

  cnt0=0;
  cnt1=0;

  PCICR  = 0x02;
  PCMSK1 = 0x03;
}

void doBeep() {
  if (digitalRead(REVERSE_PIN) == HIGH)
  {
    digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
  } 
  else digitalWrite(BEEPER, LOW);
}

void loop() {
  w.goForward(50);
  delay(2000);
  fn_display_isr();
  w.goBack(50);
  delay(2000);
}

ISR(PCINT1_vect) {
  cnt0 += PINC & (1 << PC0) >> PC0 & 1;
  cnt1 += PINC & (1 << PC1) >> PC1 & 1;
}