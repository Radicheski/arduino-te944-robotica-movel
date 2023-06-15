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
// #define OFFSET_FACTOR 0.25
#define SPEED 60

#define TURN_DELAY 200

Bridge bridge = {FRONT_LEFT, REAR_LEFT, PWM_LEFT, FRONT_RIGHT, REAR_RIGHT, PWM_RIGHT};

#define MIN_SETPOINT 50
#define FREE_PATH_THRESHOLD 150

#define DISTANCIA_MINIMA_OBSTACULO 150

#define SAMPLE_TIME 100

long frontDistance;
long leftDistance;
long rightDistance;

void setup() {
  setupBridge(&bridge);

  setupSensor(&front);
  setupSensor(&left);
  setupSensor(&right);
}

void loop() {
  if (detectarObstaculoFrontal()) {
    contornarObstaculo();
  } else {
    // moverParaFrente();
    moveForward();
  }
}

void contornarObstaculo() {
  turnLeft();
  while(detectarObstaculoEsquerda()) {
    moveForward();
  }
  turnRight();
}

int detectarObstaculoFrontal() {
  // int leituraSensor = analogRead(SENSOR_FRONTAL_PINO);
  frontDistance = getDistance(&front);
  if (frontDistance < DISTANCIA_MINIMA_OBSTACULO) {
    moveBackward();
    delay(500);
    return 1;  // Obstáculo detectado
  } else {
    return 0;  // Nenhum obstáculo detectado
  }
}

int detectarObstaculoEsquerda() {
  // int leituraSensor = analogRead(SENSOR_ESQUERDA_PINO);
  leftDistance = getDistance(&left);
  if (leftDistance < DISTANCIA_MINIMA_OBSTACULO) {
    return 1;  // Obstáculo detectado
  } else {
    return 0;  // Nenhum obstáculo detectado
  }
}

int detectarObstaculoDireita() {
  // int leituraSensor = analogRead(SENSOR_DIREITA_PINO);
  rightDistance = getDistance(&right);
  if (rightDistance < DISTANCIA_MINIMA_OBSTACULO) {
    return 1;  // Obstáculo detectado
  } else {
    return 0;  // Nenhum obstáculo detectado
  }
}

void turnLeft() {
  turnLeft(&bridge, 100);
  delay(TURN_DELAY);
}

void turnRight() {
  turnRight(&bridge, 100);
  delay(TURN_DELAY);
}

void moveForward() {
  // speed: 60 diff: 10
  // speed: 80 diff: 13
  moveForward(&bridge, SPEED);
}

void moveBackward() {
  // speed: 60 diff: -10
  // speed: 60 diff: -13
  moveBackward(&bridge, SPEED);
}

void stop() {
  stop(&bridge);
}
