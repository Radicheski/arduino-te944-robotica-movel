#include <Ultrasonic.h>

#include "Bridge.h"

#define FRONT_TRIGGER 2
#define FRONT_ECHO 3

#define LEFT_TRIGGER 8
#define LEFT_ECHO 9

#define RIGHT_TRIGGER 10
#define RIGHT_ECHO 11

Ultrasonic front(FRONT_TRIGGER, FRONT_ECHO);
Ultrasonic left(LEFT_TRIGGER, LEFT_ECHO);
Ultrasonic right(RIGHT_TRIGGER, RIGHT_ECHO);

#define FRONT_LEFT 5
#define REAR_LEFT 4
#define PWM_LEFT 12

#define FRONT_RIGHT 6
#define REAR_RIGHT 7
#define PWM_RIGHT 13

Bridge bridge = {FRONT_LEFT, REAR_LEFT, PWM_LEFT, FRONT_RIGHT, REAR_RIGHT, PWM_RIGHT};

#define MIN_SETPOINT 30
#define MAX_SETPOINT MIN_SETPOINT + 10

long distance;

void setup() {
  setupBridge(&bridge);
}

void loop() {
  distance = front.read();

  if (distance < MIN_SETPOINT) {
    moveBackward(&bridge, 0);
  } else if (distance > MAX_SETPOINT) {
    moveForward(&bridge, 0);
  } else {
    stop(&bridge);
  }

  delay(100);
}
