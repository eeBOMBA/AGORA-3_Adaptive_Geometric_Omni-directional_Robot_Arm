#include <AccelStepper.h>

//Pin Assignments
#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4
#define MS1 5
#define MS2 6
#define MS3 7

#define BTN_CW 8
#define BTN_CCW 9

//Stepper Setup
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

const int runSpeed = 600;     // steps/sec 
const int runAccel = 300;     // acceleration 

unsigned long lastMoveTime = 0;
const unsigned long idleHoldDelay = 50000; // ms before disabling motor

void setup() {
  // Driver pins
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  // Buttons
  pinMode(BTN_CW, INPUT_PULLUP);
  pinMode(BTN_CCW, INPUT_PULLUP);

  //microstepping (full step for max torque)
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);

  // Setup stepper
  stepper.setMaxSpeed(runSpeed);
  stepper.setAcceleration(runAccel);

  // Disable motor at startup
  digitalWrite(ENABLE_PIN, HIGH);
}

void loop() {
  unsigned long now = millis();

  //Button Control
  if (digitalRead(BTN_CW) == LOW) {
    digitalWrite(ENABLE_PIN, LOW);   // enable motor
    stepper.setSpeed(runSpeed);      // CW
    stepper.runSpeed();
    lastMoveTime = now;
  }
  else if (digitalRead(BTN_CCW) == LOW) {
    digitalWrite(ENABLE_PIN, LOW);   // enable motor
    stepper.setSpeed(-runSpeed);     // CCW
    stepper.runSpeed();
    lastMoveTime = now;
  }
  else {
    stepper.setSpeed(0);  // stop sending steps

    if (now - lastMoveTime < idleHoldDelay) {
      digitalWrite(ENABLE_PIN, LOW);   // hold torque
    } else {
      digitalWrite(ENABLE_PIN, HIGH);  // release after idle
    }
  }
}
