#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "Wheels.h"

#define ECHO_PIN A2
#define TRIG_PIN 4
#define MOTOR_ENA 6
#define MOTOR_ENB 5
#define MOTOR_IN1 11
#define MOTOR_IN2 12
#define MOTOR_IN3 8
#define MOTOR_IN4 7
#define SERVO_PIN 3

#define WHEEL_RADIUS 6.5
#define TICKS_PER_REV 20.0
#define CM_PER_TICK ((2.0 * PI * WHEEL_RADIUS) / TICKS_PER_REV)

#define EQUILIBRIUM_DIST 100.0
#define SPRING_K 4.5
#define DAMPING_C 1.5
#define MIN_PWM 150
#define DEAD_ZONE 4.0

Wheels w;
Servo srv;
LiquidCrystal_I2C lcd(0x27, 20, 4);

volatile unsigned int cnt0 = 0; 
volatile unsigned int cnt1 = 0;

unsigned int lastCnt0 = 0;
unsigned int lastCnt1 = 0;
unsigned long lastLoopTime = 0;

float currentDistance = EQUILIBRIUM_DIST; 
int currentMotorState = 0; 

ISR(PCINT1_vect) {
  cnt0 += (PINC >> PC0) & 1;
  cnt1 += (PINC >> PC1) & 1;
}

void setup_ultrasonic() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void setup_hardware() {
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_ENB, OUTPUT);
  w.attach(MOTOR_IN4, MOTOR_IN3, MOTOR_ENB, MOTOR_IN2, MOTOR_IN1, MOTOR_ENA);
  
  srv.attach(SERVO_PIN);
  srv.write(90); 

  lcd.init();
  lcd.backlight();
  
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9);
}

void setup() {
  setup_hardware();
  setup_ultrasonic();
  
  lcd.setCursor(0, 0);
  lcd.print("Damped Spring");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long now = millis();
  
  if (now - lastLoopTime >= 50) {
    float dt = (now - lastLoopTime) / 1000.0; 
    lastLoopTime = now;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH, 15000); 
    if (duration > 0) {
      currentDistance = duration * 0.0343 / 2.0;
    }

    noInterrupts();
    unsigned int c0 = cnt0;
    unsigned int c1 = cnt1;
    interrupts();

    float distL = (c0 - lastCnt0) * CM_PER_TICK;
    float distR = (c1 - lastCnt1) * CM_PER_TICK;
    lastCnt0 = c0;
    lastCnt1 = c1;

    float speedCmS = ((distL + distR) / 2.0) / dt;
    if (currentMotorState < 0) speedCmS = -speedCmS;

    float displacement = currentDistance - EQUILIBRIUM_DIST; 
    
    float force = (SPRING_K * displacement) - (DAMPING_C * speedCmS);

    if (abs(displacement) <= DEAD_ZONE) {
      w.stop();
      currentMotorState = 0;
      lcd.setCursor(0, 1);
      lcd.print("Eq. Zone      ");
    } 
    else if (force > 0) {
      int pwm = constrain(abs(force) + MIN_PWM, 0, 255);
      w.forward();
      w.setSpeed(pwm);
      currentMotorState = 1;
      
      lcd.setCursor(0, 1);
      lcd.print("FWD >> PWM:");
      lcd.print(pwm);
      lcd.print("  ");
    } 
    else {
      int pwm = constrain(abs(force) + MIN_PWM, 0, 255);
      w.back();
      w.setSpeed(pwm);
      currentMotorState = -1;
      
      lcd.setCursor(0, 1);
      lcd.print("BCK << PWM:");
      lcd.print(pwm);
      lcd.print("  ");
    }

    lcd.setCursor(0, 0);
    lcd.print("D:");
    lcd.print(currentDistance, 1);
    lcd.print(" V:");
    lcd.print(abs(speedCmS), 1);
    lcd.print("   ");
  }
}