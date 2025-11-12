#include <Servo.h>

//Pin Assignments
const int joystickX = A0;
const int joystickY = A1;

const int servoPin = 7;

const int stepPin1 = 4;
const int dirPin1 = 5;

const int enablePin = 8;

//Servo Variables
Servo myServo;
int currentAngle = 90;
const int minAngle = 0;
const int maxAngle = 180;
const int servoStep = 1;
const int servoDeadzone = 80;
const int servoUpdateInterval = 20;  // ms
unsigned long lastServoUpdate = 0;

//Stepper Timing
unsigned long lastStepTime1 = 0;
const int stepInterval = 1000; // µs for movement
unsigned long lastMoveTime = 0;
const unsigned long idleHoldDelay = 20000; // ms before disabling completely

//Deadzone for Stepper
const int stepperDeadzone = 50; //deadzone to kill drift

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH); // disable stepper initially

  myServo.attach(servoPin);
  myServo.write(currentAngle);
}

void loop() {
  unsigned long now = millis();
  unsigned long nowMicros = micros();

  //Servo Controlled by Joystick Y
  int yVal = analogRead(joystickY);
  if (now - lastServoUpdate >= servoUpdateInterval) {
    lastServoUpdate = now;

    if (yVal > 512 + servoDeadzone) {
      if (currentAngle < maxAngle) {
        currentAngle += servoStep;
        myServo.write(currentAngle);
      }
    } else if (yVal < 512 - servoDeadzone) {
      if (currentAngle > minAngle) {
        currentAngle -= servoStep;
        myServo.write(currentAngle);
      }
    }
  }

  //Stepper Controlled by Joystick X
  int xVal = analogRead(joystickX) - 512;

  if (abs(xVal) > stepperDeadzone) {
    // Full torque while moving
    digitalWrite(enablePin, LOW);
    digitalWrite(dirPin1, xVal > 0 ? HIGH : LOW);

    if (nowMicros - lastStepTime1 > stepInterval) {
      pulse(stepPin1);
      lastStepTime1 = nowMicros;
      lastMoveTime = now; // Update last move time
    }
  } 
  else if (now - lastMoveTime < idleHoldDelay) {
    // Just hold position — no steps sent at all
    digitalWrite(enablePin, LOW);
  }
  else {
    // Fully disable after idle hold delay
    digitalWrite(enablePin, HIGH);
  }
}

//Step Pulse Function
void pulse(int pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(pin, LOW);
}
