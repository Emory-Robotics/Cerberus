#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 60  // Analog servos run at ~50 Hz updates

#define FR_ARM 0
#define FR_ELBOW 1
#define FR_SHOULDER 2

#define FL_ARM 3
#define FL_ELBOW 4
#define FL_SHOULDER 5

#define BL_ARM 6
#define BL_ELBOW 7
#define BL_SHOULDER 8

#define BR_ARM 9
#define BR_ELBOW 10
#define BR_SHOULDER 11

int LIMITS[12][2] = {
  { 110, 450 },  // 0:  FR_ARM
  { 400, 300 },  // 1:  FR_ELBOW
  { 600, 150 },  // 2:  FR_SHOULDER

  { 650, 300 },  // 3:  FL_ARM
  { 300, 400 },  // 4:  FL_ELBOW
  { 350, 110 },  // 5:  FL_SHOULDER

  { 550, 300 },  // 6:  BL_ARM
  { 450, 600 },  // 7:  BL_ELBOW
  { 475, 110 },  // 8:  BL_SHOULDER

  { 200, 500 },  // 9:  BR_ARM
  { 250, 100 },  // 10: BR_ELBOW
  { 375, 110 }   // 11: BR: SHOULDER
};

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  for (int i = 0; i < 16; i++) {
    drive(i, 0);
    delay(10);
  }
}

void loop() {
  prone();
  delay(5000);
  stand();
  delay(5000);
}

void drive(long servoID, long degree) {
  degree = constrain(degree, 0, 180);
  long minPulse = LIMITS[servoID][0];
  long maxPulse = LIMITS[servoID][1];

  // Invert servos with flipped mins and lows
  if (minPulse > maxPulse) {
    degree = 180 - degree;
    minPulse = LIMITS[servoID][1];
    maxPulse = LIMITS[servoID][0];
  }

  long pulse = map(degree, 0, 180, minPulse, maxPulse);
  pwm.setPWM(servoID, 0, pulse);
}

void driveShoulders(long degree) {
  drive(FL_SHOULDER, degree);
  drive(FR_SHOULDER, degree);
  drive(BL_SHOULDER, degree);
  drive(BR_SHOULDER, degree);
}

void driveArms(long degree) {
  drive(FL_ARM, degree);
  drive(FR_ARM, degree);
  drive(BL_ARM, degree);
  drive(BR_ARM, degree);
}

void driveElbows(long degree) {
  drive(FL_ELBOW, degree);
  drive(FR_ELBOW, degree);
  drive(BL_ELBOW, degree);
  drive(BR_ELBOW, degree);
}

void prone() {
  drive(FL_ARM, 0);
  drive(FL_ELBOW, 0);
  drive(FL_SHOULDER, 0);

  drive(FR_ARM, 0);
  drive(FR_ELBOW, 0);
  drive(FR_SHOULDER, 0);

  drive(BL_ARM, 0);
  drive(BL_ELBOW, 0);
  drive(BL_SHOULDER, 0);

  drive(BR_ARM, 0);
  drive(BR_ELBOW, 0);
  drive(BR_SHOULDER, 0);
}

void stand() {
  drive(FL_ARM, 90);
  drive(FL_ELBOW, 90);
  drive(FL_SHOULDER, 0);

  drive(FR_ARM, 90);
  drive(FR_ELBOW, 90);
  drive(FR_SHOULDER, 0);

  drive(BL_ARM, 50);
  drive(BL_ELBOW, 150);
  drive(BL_SHOULDER, 0);

  drive(BR_ARM, 50);
  drive(BR_ELBOW, 150);
  drive(BR_SHOULDER, 0);
}