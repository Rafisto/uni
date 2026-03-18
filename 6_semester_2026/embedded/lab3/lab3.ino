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

Ticker move(fn_move_refresh, fn_move);
Ticker display(fn_display_refresh, fn_display);

void setup() {
  w.attach(7, 8, 5, 12, 11, 10);
  lcd.init();
  lcd.backlight();
}

void loop() {
  move.check();
  display.check();
}
