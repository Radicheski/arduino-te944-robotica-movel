#include "Bridge.h"
#include <Arduino.h>

void setupBridge(Bridge *b) {
  pinMode(b->frontLeft, OUTPUT);
  pinMode(b->rearLeft, OUTPUT);
  pinMode(b->frontRight, OUTPUT);
  pinMode(b->rearRight, OUTPUT);
}

void stop(Bridge *b) {
  digitalWrite(b->rearLeft, HIGH);
  digitalWrite(b->rearRight, HIGH);
  digitalWrite(b->frontLeft, HIGH);
  digitalWrite(b->frontRight, HIGH);
}

void moveForward(int front, int rear, int pwm, int speed) {
  digitalWrite(front, HIGH);
  digitalWrite(rear, LOW);
  analogWrite(pwm, speed);
}

void moveBackward(int front, int rear, int pwm, int speed) {
  digitalWrite(front, LOW);
  digitalWrite(rear, HIGH);
  analogWrite(pwm, speed);
}

void moveForward(Bridge *b, int speed) {
  moveForward(b->frontLeft, b->rearLeft, b->pwmLeft, speed);
  moveForward(b->frontRight, b->rearRight, b->pwmRight, speed);
}

void moveBackward(Bridge *b, int speed) {
  moveBackward(b->frontLeft, b->rearLeft, b->pwmLeft, speed);
  moveBackward(b->frontRight, b->rearRight, b->pwmRight, speed);
}

void turnLeft(Bridge *b, int speed) {
  moveBackward(b->frontLeft, b->rearLeft, b->pwmLeft, speed);
  moveForward(b->frontRight, b->rearRight, b->pwmRight, speed);
}

void turnRight(Bridge *b, int speed) {
  moveForward(b->frontLeft, b->rearLeft, b->pwmLeft, speed);
  moveBackward(b->frontRight, b->rearRight, b->pwmRight, speed);
}
