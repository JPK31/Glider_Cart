#include "servo.h"


//--------------------------------------------
//  Fonction command servo_motor with delay
//--------------------------------------------


int servo_angle = 90;

void servo ( float diffAngle, float turnRight, int servo_pin)
{
  if (diffAngle > 5  && turnRight)
    servo_angle = 95;

  if (diffAngle > 5 && !turnRight)
    servo_angle = 85;

  if (diffAngle > 25 && turnRight)
    servo_angle = 120;

  if (diffAngle > 25 && !turnRight)
    servo_angle = 60;

  if (diffAngle > 60 && turnRight)
    servo_angle = 160;

  if (diffAngle > 60 && !turnRight)
    servo_angle = 20;

  if (diffAngle < 5 )
    servo_angle = 90;

  int pulseMicros = map(servo_angle, 0, 180, 1000, 2000);

  for (int i = 0; i < 32; i++)
  {
    digitalWrite(servo_pin, HIGH);
    delayMicroseconds(pulseMicros);
    digitalWrite(servo_pin, LOW);
    delayMicroseconds(20000);
    digitalWrite(servo_pin, HIGH);
  }


}





