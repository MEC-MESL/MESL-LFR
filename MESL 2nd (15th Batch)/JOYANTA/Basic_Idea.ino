
#define sensorCount 5

// If bot is going toward opposite direction of you, left is sensor_1.
const uint8_t sensorPins[sensorCount] = { A0, A1, A2, A3, A4 };
// { GND, VCC, PWM }
const uint8_t leftMotorPins[3] = { 4, 5, 6 };
const uint8_t rightMotorPins[3] = { 7, 8, 9 };

uint8_t activeSensor = 0;
bool onPath[sensorCount] = { false };
bool onGroundAll = false;
bool onPathAll = false;

// Calculated values.
float error = 0.0F;
float previousError = 0.0F;
float integral = 0.0F;
float pidValue = 0.0F;

// Sensitivity.
const float kP = 0.0F;
const float kI = 0.0F;
const float kD = 0.0F;


// Function declaration.
void readSensorArray();
void drive(float driveValue);
void sprint();
void spin(bool left);
void brake(bool hard);


// Main()
void setup() {
  srand(0);
  Serial.begin(9600);
  setPinMode();
}

void loop() {
  readSensorArray();
  drive(pidValue);
  delay(100);
}
