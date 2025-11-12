#include <Servo.h>

Servo servoA1;
Servo servoA2;
Servo servoA3;

const int servoA1Pin = 3;
const int servoA2Pin = 4;
const int servoA3Pin = 5;

//Controls
const int joystickY = A0;
const int gentleGripButton = 6; 

//ACS712 Current Sensor 
const int currentSensorPin = A1; 
const float sensitivity = 0.185; // For ACS712-5A use 0.185, for 20A use 0.1, for 30A use 0.066
const float zeroCurrentVoltage = 2.5; 
float gripCurrentThreshold = 0.065; // Amps to stop grip


//Adjustable Servo Limits 
int A1_min = 8;   
int A1_max = 80;  

int A2_min = 100; 
int A2_max = 180; 

int A3_min = 100; 
int A3_max = 180; 
// ===================================

int posA1 = A1_min;
int posA2 = A2_max;
int posA3 = A3_max;

const int speedDelay = 60;  
const int gentleDelay = 120; 

bool gripReached = false; // stops re-closing while button is held

// ===== Adjustable back-off after grip =====
const int releaseOffset = 1; // degrees to move back after reaching grip threshold
// ==========================================

void setup() {
  servoA1.attach(servoA1Pin);
  servoA2.attach(servoA2Pin);
  servoA3.attach(servoA3Pin);

  pinMode(gentleGripButton, INPUT_PULLUP);

  servoA1.write(posA1);
  servoA2.write(posA2);
  servoA3.write(posA3);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(gentleGripButton) == LOW && !gripReached) {
    gentleGripWithCurrentLimit();
  } 
  else if (digitalRead(gentleGripButton) == HIGH) {
    gripReached = false; // reset for next press
    joystickControl();
  }
  else {
    joystickControl();
  }
}

void joystickControl() {
  int joyY = analogRead(joystickY);
  int center = 512;
  int deadzone = 50;

  if (abs(joyY - center) > deadzone) {
    int direction = (joyY < center) ? -1 : 1; 
    int stepSize = map(abs(joyY - center), 0, 512, 1, 4); 

    posA1 = constrain(posA1 + (direction * stepSize), A1_min, A1_max);
    posA2 = constrain(posA2 - (direction * stepSize), A2_min, A2_max);
    posA3 = constrain(posA3 - (direction * stepSize), A3_min, A3_max);

    servoA1.write(posA1);
    servoA2.write(posA2);
    servoA3.write(posA3);

    delay(speedDelay);
  }
}

// === NEW: Averaged current reading ===
float readAverageCurrent(int samples = 10) {
  float sum = 0;
  for (int i = 0; i < samples; i++) {
    int sensorValue = analogRead(currentSensorPin);
    float voltage = (sensorValue / 1023.0) * 5.0;
    float current = (voltage - zeroCurrentVoltage) / sensitivity;
    sum += abs(current);
    delay(2); // short delay for stable reading
  }
  return sum / samples;
}

void gentleGripWithCurrentLimit() {
  while (true) {
    float current = readAverageCurrent(15); // use averaged value

    // DEBUG: Show averaged current readings
    Serial.print("Average current: ");
    Serial.println(current);

    // Stop if threshold reached
    if (current >= gripCurrentThreshold) {
      Serial.println("Max grip reached — stopping!");

      // Back off a little to avoid buzzing
      posA1 = max(A1_min, posA1 - releaseOffset);
      posA2 = min(A2_max, posA2 + releaseOffset);
      posA3 = min(A3_max, posA3 + releaseOffset);

      // Send final holding positions ONCE
      servoA1.write(posA1);
      servoA2.write(posA2);
      servoA3.write(posA3);

      gripReached = true;
      break; // Exit loop so servos stop moving
    }

    // Smooth slow-down near object
    float loadRatio = current / gripCurrentThreshold;
    int delayTime = map(loadRatio * 100, 0, 100, gentleDelay, gentleDelay * 4);

    bool moved = false;
    if (posA1 < A1_max) { posA1++; moved = true; }
    if (posA2 > A2_min) { posA2--; moved = true; }
    if (posA3 > A3_min) { posA3--; moved = true; }

    if (moved) {
      servoA1.write(posA1);
      servoA2.write(posA2);
      servoA3.write(posA3);
      delay(delayTime);
    } else {
      gripReached = true;
      break;
    }
  }
}
