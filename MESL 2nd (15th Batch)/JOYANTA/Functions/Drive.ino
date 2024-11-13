void drive(float driveValue) {
  uint8_t leftPWM = 127 - driveValue * 127;
  uint8_t rightPWM = 127 + driveValue * 127;

  digitalWrite(leftMotorPins[0], 0);
  digitalWrite(leftMotorPins[1], 1);

  digitalWrite(rightMotorPins[0], 0);
  digitalWrite(rightMotorPins[1], 1);

  analogWrite(leftMotorPins[2], leftPWM);
  analogWrite(rightMotorPins[2], rightPWM);
}


void sprint(float driveValue) {
  uint8_t leftPWM;
  uint8_t rightPWM;

  if (driveValue == 0) {
    leftPWM = 255;
    rightPWM = 255;
  }
  if (driveValue < 0) {
    rightPWM = 255;
    leftPWM = 255 - driveValue * 127;
  }
  else {
    rightPWM = 255 - driveValue * 127;
    leftPWM = 255;
  }

  drive(driveValue);

  analogWrite(leftMotorPins[2], leftPWM);
  analogWrite(rightMotorPins[2], rightPWM);
}


void brake(bool hard) {
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

  analogWrite(leftMotorPins[2], 127);
  analogWrite(rightMotorPins[2], 127);
}
