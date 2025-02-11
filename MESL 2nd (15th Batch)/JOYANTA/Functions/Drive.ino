void drive(float driveValue) {
  uintt_t power = min(127, basePower);
  uint8_t leftPWM = (1.0F - driveValue) * basePower;
  uint8_t rightPWM = (1.0F - driveValue) * basePower;

  digitalWrite(leftMotorPins[0], 0);
  digitalWrite(leftMotorPins[1], 1);

  digitalWrite(rightMotorPins[0], 0);
  digitalWrite(rightMotorPins[1], 1);

  analogWrite(leftMotorPins[2], leftPWM);
  analogWrite(rightMotorPins[2], rightPWM);
}


void sprint(float driveValue) {
  uint8_t leftPWM = 255;
  uint8_t rightPWM = 255;

  if (driveValue < 0) {
    leftPWM = (1.0F - abs(driveValue)) * 255;
  }
  else {
    rightPWM = (1.0F - abs(driveValue)) * 255;
  }

  drive(driveValue);

  analogWrite(leftMotorPins[2], leftPWM);
  analogWrite(rightMotorPins[2], rightPWM);
}


void brake(bool hard = false) {
  digitalWrite(leftMotorPins[0], hard);
  digitalWrite(leftMotorPins[1], hard);

  digitalWrite(rightMotorPins[0], hard);
  digitalWrite(rightMotorPins[1], hard);

  analogWrite(leftMotorPins[2], 0);
  analogWrite(rightMotorPins[2], 0);
}

void spin(bool left) {
  digitalWrite(leftMotorPins[0], left);
  digitalWrite(leftMotorPins[1], !left);

  digitalWrite(rightMotorPins[0], !left);
  digitalWrite(rightMotorPins[1], left);

  analogWrite(leftMotorPins[2], basePower);
  analogWrite(rightMotorPins[2], basePower);
}
