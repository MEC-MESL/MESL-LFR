#define sensorCount 5
#define threshHold 950
const uint8_t leftMotorPins[2] = { 7, 6 };
const uint8_t rightMotorPins[2] = { 4, 5 };
const uint8_t sensorPins[sensorCount] = { A0, A1, A2, A3, A4 };

bool onLine[sensorCount] = { false };
bool onLinePrevious[sensorCount] = { false };
uint8_t activeSensor = 0;
uint8_t activeSensorPrevious = 0;
float error = 0.0F, errorPrevious = 0.0F;
float proportional = 0.0F;
float derivative = 0.0F;
float integral = 0.0F;
float pidValue = 0.0F;
long timeStamp = 0;

uint8_t basePower = 253;
float kP = 0.6F;
float kI = 0.02F;
float kD = 0.2F;

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

  if (error == 0.0F) {
    integral = 0.0F;
    derivative = 0.0F;
  }


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
  digitalWrite(leftMotorPins[1], !left);

  digitalWrite(rightMotorPins[0], !left);
  digitalWrite(rightMotorPins[1], left);
}

void reverse() {
  digitalWrite(leftMotorPins[0], 1);
  digitalWrite(leftMotorPins[1], 0);

  digitalWrite(rightMotorPins[0], 1);
  digitalWrite(rightMotorPins[1], 0);
}

void stop() {
  digitalWrite(leftMotorPins[0], 0);
  digitalWrite(rightMotorPins[0], 0);

  digitalWrite(leftMotorPins[1], 0);
  digitalWrite(rightMotorPins[1], 0);
}

int scanForthinLine() {
  for (int i = 0; i < 80; i++) {
    readSensor();
    if (activeSensor != 0) {
      return 1;
    }
    spin((errorPrevious >= 0) ^ (i < 20 || i > 60));
  }
  return 0;
}

void turn(bool left) {
  do {
    readSensor();
    spin(left);
  } while (!onLine[2]);
}

void setup() {
  setPinModes();
  Serial.begin(9600);
}

void loop() {
  readSensor();

  if (activeSensor == sensorCount) {
    // Possibilities:
    // 1. T
    // 2. X
    stop();
    delay(1000);

    drive(0);
    delay(100);
    stop();
    delay(1000);

    while (true) {
      spin(false);
    }

  }
  else if (activeSensor > 1) {
    if (onLine[0] && onLine[2] && !onLine[4]) {
      do {
        readSensor();
        drive(0);
      } while (onLine[0]);
      readSensor();
      if (activeSensor == 0) {
        // Left
        drive(0);
        delay(100);
        turn(true);
      }
      else {
        drive(pidValue);
      }
    }
    else if (!onLine[0] && onLine[2] && onLine[4]) {
      do {
        readSensor();
        drive(0);
      } while (onLine[4]);
      readSensor();
      if (activeSensor == 0) {
        // Right.
        drive(0);
        delay(100);
        turn(false);
      }
      else {
        drive(pidValue);
      }
    }
  }
  else if (activeSensor == 1) {
    if (onLine[2]) {
      drive(0);
    }
    else {
      drive(pidValue);
    }
  }
  else if (activeSensor == 0) {
    if (scanForthinLine()) {
      drive(pidValue);
    }
    else {
    // Spin 180
      do {
        readSensor();
        spin(true);
      } while (!onLine[2]);
    }
  }
  else {
    drive(pidValue);
  }
}