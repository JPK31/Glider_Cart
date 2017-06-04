#ifndef GLIDER_CART_H_
# define GLIDER_CART_H_

/*----------------------------
 *      CONFIGURATION
 *---------------------------*/

# include <TinyGPS++.h>
# include <Wire.h>
# include "mag.h"
# include "direct.h"
# include "servo.h"
TinyGPSPlus gps;


/*-------------------------------------------
     declaration variables et initialisation
 -------------------------------------------*/

float HomeLat = 42.0;
float HomeLng = 1.5;
float distHome = 0.0;
float courseHome = 0.0;
float headingMag = 0.0;
float diffAngle = 0.0;
int motorSpeed = 45;
String Command = "home";
String fix = "wait fix";
bool turnRight = false;

/*----------------------------
      pin assignement
-----------------------------*/

# define pin_home 8
# define pin_dir 6
# define pin_vit 7
# define pin_Rx 19
# define pin_Tx 18

#endif

