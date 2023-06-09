#ifndef Ultrasonic_h
#define Ultrasonic_h

typedef struct {
  int trigger;
  int echo;
} Ultrasonic;

void setupSensor(Ultrasonic *s);

long getDistance(Ultrasonic *s);

#endif
