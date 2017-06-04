#ifndef SERVO_H_
# define SERVO_H_

# include <Arduino.h>

void servo ( float diffAngle, float turnRight, int servo_pin);

extern int servo_angle;
#endif
