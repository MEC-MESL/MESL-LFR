#define sensorCount 5
#define threshHold 950
const uint8_t leftMotorPins[2] = { 7, 6 };
const uint8_t rightMotorPins[2] = { 4, 5 };
const uint8_t sensorPins[sensorCount] = { A0, A1, A2, A3, A4 };

bool onLine[sensorCount] = { false };
bool onLinePrevious[sensorCount] = { false };
uint8_t activeSensor = 0;
float error = 0.0F, errorPrevious = 0.0F;
float proportional = 0.0F;
float derivative = 0.0F;
float integral = 0.0F;
float pidValue = 0.0F;
long timeStamp = 0;

uint8_t basePower = 255;
float kP = 0.0F;
float kI = 0.0F;
float kD = 0.0F;

void setPinModes() {
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(leftMotorPins[i], 0x1);
    pinMode(rightMotorPins[i], 0x1);
  }
}

void readSensor() {
  delay(10);
  activeSensor = 0;
  uint8_t sensorEffect = 0;
  for (uint8_t i = 0; i < sensorCount; i++) {
    onLine[i] = analogRead(sensorPins[i]) < threshHold;
    activeSensor += onLine[i];
    sensorEffect += onLine[i] * i;
  }
  if (activeSensor > 0) {
    for (uint8_t i = 0; i < sensorCount; i++) {
      onLinePrevious[i] = onLine[i];
    }
    errorPrevious = error;
    error = (float) sensorEffect / (float) activeSensor / 2.0F - 1.0F;
  }

  proportional = min(1.0F, max(-1.0F, error * kP));
  integral = min(1.0F, max(-1.0F, integral + error * kI));
  derivative = min(1.0F, max(-1.0F, error - errorPrevious));

  pidValue = min(1.0F, max(-1.0F, proportional + integral + derivative));
}

void drive(float driveValue) {
  uint8_t leftPWM = basePower;
  uint8_t rightPWM = basePower;
  if (driveValue < 0.0F) {
    // Left
    leftPWM = min(255, max(0, basePower - basePower * abs(driveValue)));
  }
  else if (driveValue > 0.0F) {
    // Right
    rightPWM = min(255, max(0, basePower - basePower * abs(driveValue)));
  }

  digitalWrite(leftMotorPins[0], 0);
  digitalWrite(rightMotorPins[0], 0);

  analogWrite(leftMotorPins[1], leftPWM);
  analogWrite(rightMotorPins[1], rightPWM);
}

void spin(bool left) {
  digitalWrite(leftMotorPins[0], left);
  analogWrite(leftMotorPins[1], 127);

  digitalWrite(rightMotorPins[0], !left);
  analogWrite(rightMotorPins[1], 127);
}

void stop() {
  digitalWrite(leftMotorPins[0], 0);
  digitalWrite(rightMotorPins[0], 0);

  digitalWrite(leftMotorPins[1], 0);
  digitalWrite(rightMotorPins[1], 0);
}

void setup() {
  setPinModes();
  Serial.begin(9600);
}

void loop() {
  readSensor();
  if (activeSensor == 0) {
    if (onLinePrevious[0] && onLinePrevious[1] && onLinePrevious[2] && onLinePrevious[3] && onLinePrevious[4]) {
      // Both
      // Pick default
      do {
        readSensor();
        spin(false);
      } while (!onLine[2]);
    }
    if (onLinePrevious[0] && onLinePrevious[1] && onLinePrevious[2]) {
      // Left
      do {
        readSensor();
        spin(true);
      } while (!onLine[2]);
    }
    else if (onLinePrevious[2] && onLinePrevious[3] && onLinePrevious[4]) {
      do {
        // Right
        readSensor();
        spin(false);
      } while (!onLine[2]);
    }
    else {
      drive(pidValue);
    }
  }
  else if (activeSensor == 1) {
    int i = (abs(error - errorPrevious) <= 0.0F) ? 1 : -1;
    basePower = min(255, max(0, basePower + i));
    drive(pidValue);
  }
  else {
    basePower = 127;
    drive(pidValue);
  }
}
