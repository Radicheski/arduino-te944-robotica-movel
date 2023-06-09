#include <Arduino.h>
#include "Ultrasonic.h"

void setupSensor(Ultrasonic *s) {
  pinMode(s->trigger, OUTPUT);
  pinMode(s->echo, INPUT);

  digitalWrite(s->trigger, LOW);
}

void trigger(Ultrasonic *s) {
    digitalWrite(s->trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(s->trigger, LOW);
}

long getDistance(Ultrasonic *s) {
    trigger(s);
    return 340 * pulseIn(s->echo, HIGH) / 1000 / 2;
}
