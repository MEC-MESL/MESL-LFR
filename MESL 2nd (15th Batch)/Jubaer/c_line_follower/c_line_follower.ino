#define inA     11
#define inB     10
#define inC     9
#define inD     8
#define enA     6
#define enB     5
// #define inA     12
// #define inB     13
// #define inC     11
// #define inD     8
// #define enA     10
// #define enB     9



int leftBaseSpeed   = 80; //170
int rightBaseSpeed  = 80; //170
int maxSpeed        = 80; //255

#define NUM_SENSORS    8

int sValues[NUM_SENSORS], lastSensor;

float kp            = 8;
float kd            = 8;
int prevError;

void initialize();
void lineFollow();
int readSensor();
void wheel();

void setup() {
  
  initialize();
  

}

void loop() {

  
  lineFollow();
  

}
