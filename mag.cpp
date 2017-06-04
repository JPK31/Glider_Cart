//--------------------------------------------------------
//  Give magnetic heading from HMC5883 magnetometer/compass
//--------------------------------------------------------
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <wire.h>
#include "mag.h"


Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

float headingDeg()
{
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);


  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // South of france is 0.5° that can be aproximate to zero.

  float declinationAngle = 0.0;
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  heading = heading * 180 / M_PI;
  Serial.print(heading);
  return (heading);
}
