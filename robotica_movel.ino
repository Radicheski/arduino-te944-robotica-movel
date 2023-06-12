#include "Ultrasonic.h"
#include "Bridge.h"

#define FRONT_TRIGGER 2
#define FRONT_ECHO 3

#define LEFT_TRIGGER 8
#define LEFT_ECHO 9

#define RIGHT_TRIGGER 10
#define RIGHT_ECHO 11

Ultrasonic front = {FRONT_TRIGGER, FRONT_ECHO};
Ultrasonic left = {LEFT_TRIGGER, LEFT_ECHO};
Ultrasonic right = {RIGHT_TRIGGER, RIGHT_ECHO};

#define FRONT_LEFT 13   // IN2
#define REAR_LEFT 4     // IN1
#define PWM_LEFT 6      // ENA

#define FRONT_RIGHT 12  // IN3
#define REAR_RIGHT 7    // IN4
#define PWM_RIGHT 5     // ENB


// speed: 80 factor: 0.2
// speed: 160 factor 0.33
#define OFFSET_FACTOR 0.2
#define SPEED 80

Bridge bridge = {FRONT_LEFT, REAR_LEFT, PWM_LEFT, FRONT_RIGHT, REAR_RIGHT, PWM_RIGHT};

#define MIN_SETPOINT 300
#define MAX_SETPOINT MIN_SETPOINT + 100

#define SAMPLE_TIME 100

long frontDistance;
long leftDistance;
long rightDistance;

long diff;

long finalDestination[] = {2147483647, -2147483648};
long currentPosition[2];
int direction[] = {1, 0};

void setup() {
  setupBridge(&bridge);

  setupSensor(&front);
  setupSensor(&left);
  setupSensor(&right);

  finalDestination[0] = 800;
  finalDestination[1] = 0;
}

void loop() {

  while (finalDestination[0] > currentPosition[0] ) {
    moveForward();
  }
  
  finalDestination[0] = 0;

  turnLeft();
  turnLeft();

  while (finalDestination[0] < currentPosition[0] ) {
    moveForward();
  }

  while(1);
}

void getDistances() {
  frontDistance = getDistance(&front);
  leftDistance = getDistance(&left);
  rightDistance = getDistance(&right);

  // speed: 60 diff: 50
  // speed: 80 diff: 37
  diff = (rightDistance - leftDistance) / 37;
}

void turnLeft() {
  turnLeft(&bridge, SPEED);
  delay(500);
  stop(&bridge);

  if (direction[0] == 1) {
    direction[0] = 0;
    direction[1] = -1;
  } else if (direction[0] == -1) {
    direction[0] = 0;
    direction[1] = 1;
  } else if (direction[1] == 1) {
    direction[0] = 1;
    direction[1] = 0;
  } else if (direction[1] == -1) {
    direction[0] = -1;
    direction[1] = 0;
  }
}

void turnRight() {
  turnRight(&bridge, SPEED);
  delay(500);
  stop(&bridge);

  if (direction[0] == 1) {
    direction[0] = 0;
    direction[1] = 1;
  } else if (direction[0] == -1) {
    direction[0] = 0;
    direction[1] = -1;
  } else if (direction[1] == 1) {
    direction[0] = -1;
    direction[1] = 0;
  } else if (direction[1] == -1) {
    direction[0] = 1;
    direction[1] = 0;
  }
}

void moveForward() {
  // speed: 60 diff: 10
  // speed: 80 diff: 13
  moveForward(&bridge, SPEED, SPEED * OFFSET_FACTOR + diff);

  long start = millis();
  while (millis() - start < SAMPLE_TIME);

  stop(&bridge);

  currentPosition[0] += SPEED * direction[0];
  currentPosition[1] += SPEED * direction[1];
}

void moveBackward() {
  // speed: 60 diff: -10
  // speed: 60 diff: -13
  moveBackward(&bridge, SPEED, -SPEED * OFFSET_FACTOR + diff);

  long start = millis();
  while (millis() - start < SAMPLE_TIME);

  stop(&bridge);

  currentPosition[0] -= SPEED * direction[0];
  currentPosition[1] -= SPEED * direction[1];
}

void stop() {
  stop(&bridge);
}
