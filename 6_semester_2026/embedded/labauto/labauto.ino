#include <Servo.h>
#include "Wheels.h"

#define SPEED 200
#define BT_INTERVAL 100
#define SETTLE_DELAY 250  // Small pause (ms) after a turn or straight to eliminate momentum drift

const long TICKS_STRAIGHT = 5; 
const long TICKS_90_TURN = 20;   

Wheels w;
Servo srv;

volatile int raw_cnt0 = 0;  
volatile int raw_cnt1 = 0;
long total_cnt0 = 0, total_cnt1 = 0;  

int dirL = 0;  
int dirR = 0;
unsigned long lastBTTime = 0;

// Step Sequencer Structure
enum Action { MOVE_FORWARD, ROTATE_LEFT, ROTATE_RIGHT };

struct Step {
  Action action;
  long targetDelta;
};

// Complete 14-step layout for a double-loop square figure-8
const int TOTAL_STEPS = 14;
Step path[TOTAL_STEPS] = {
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Left Square: Side 1 (North)
  {ROTATE_LEFT,  TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Left Square: Side 2 (West)
  {ROTATE_LEFT,  TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Left Square: Side 3 (South)
  {ROTATE_LEFT,  TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Left Square: Side 4 (East - Back to center)
  
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Right Square: Side 1 (Continuing East)
  {ROTATE_RIGHT, TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Right Square: Side 2 (South)
  {ROTATE_RIGHT, TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}, // Right Square: Side 3 (West)
  {ROTATE_RIGHT, TICKS_90_TURN},
  {MOVE_FORWARD, TICKS_STRAIGHT}  // Right Square: Side 4 (North - Back to center)
};

int currentStep = 0;
long startTickL = 0;
long startTickR = 0;
bool stepInitialized = false;

void moveRobot(int l, int r, void (Wheels::*m)()) {
  dirL = l;
  dirR = r;
  (w.*m)();
  w.setSpeed(SPEED);
}

#define MOTOR_ENA 6   
#define MOTOR_ENB 5   
#define MOTOR_IN1 11  
#define MOTOR_IN2 12  
#define MOTOR_IN3 8   
#define MOTOR_IN4 7   
void setup_motor() {
  pinMode(6, MOTOR_ENA);
  pinMode(5, MOTOR_ENB);
  w.attach(MOTOR_IN4, MOTOR_IN3, MOTOR_ENB, MOTOR_IN2, MOTOR_IN1, MOTOR_ENA);
}

void setup() {
  setup_motor();
  srv.attach(3);
  srv.write(90); // Lock servo straight

  Serial.begin(9600);
  for (int i = 0; i < 10; ++i) {
    Serial.println("reset");
    delay(100);
  }

  // Encoder Interrupts
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9);
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

void handleSquareFigure8() {
  // Loop back to the beginning of the sequence infinitely
  if (currentStep >= TOTAL_STEPS) {
    currentStep = 0;
  }

  Step s = path[currentStep];

  // Initialize the metrics at the start of a new step segment
  if (!stepInitialized) {
    startTickL = total_cnt0;
    startTickR = total_cnt1;
    stepInitialized = true;

    switch (s.action) {
      case MOVE_FORWARD:
        Serial.println("Move Forward");
        moveRobot(1, 1, &Wheels::forward);
        break;
      case ROTATE_LEFT:
        Serial.println("Move Left");
        moveRobot(1, 0, &Wheels::forwardLeft); 
        break;
      case ROTATE_RIGHT:
        Serial.println("Move Right");
        moveRobot(0, 1, &Wheels::forwardRight); 
        break;
    }
  }

  // Calculate absolute distance traveled during this specific step
  long deltaL = abs(total_cnt0 - startTickL);
  long deltaR = abs(total_cnt1 - startTickR);
  long currentDelta = (deltaL + deltaR) / 2; // Average encoder progress

  // Check if step objective has been reached
  if (currentDelta >= s.targetDelta) {
    moveRobot(0, 0, &Wheels::stop);
    delay(SETTLE_DELAY); // Crucial pause to let physics settle for crisp corners
    
    stepInitialized = false;
    currentStep++; // Move to the next step index
  }
}

void loop() {
  processCounts();
  sendBTData();          // Feeds your live Python 2D map tracker
  handleSquareFigure8(); // Executes path state sequence
}

volatile uint8_t last_PINC = 0; // Add this global variable at the top

ISR(PCINT1_vect) {
  uint8_t current_PINC = PINC;
  uint8_t changed = current_PINC ^ last_PINC; // Identifies which pins actually flipped
  last_PINC = current_PINC;

  // Only count if the pin changed AND it is currently HIGH (Rising Edge)
  if ((changed & (1 << PC0)) && (current_PINC & (1 << PC0))) raw_cnt0++;
  if ((changed & (1 << PC1)) && (current_PINC & (1 << PC1))) raw_cnt1++;
}