
/*  ------------------------------------------
 *   Commande retour home chariot planeur version 1.0
 *  -----------------------------------------
 *  Ce code permet de piloter un vehicule et un "retour maison" a partir d'une radio commande modelisme
 *  le chhariot est piloté a partir d'un module GPS pour la position et le calcul de la route
 *  et d'un capteur compas magnetique pour la  tenue du cap
 *  la position du servo de direction est asservie sur la difference entre le cap suivie et la route ideale.
 *  Le code a été testé avec  avec des modules GPS Ublox Neo m6n ou Ublox m8n configuré en mode MNEA et à la frequence 4800 Bauds.
 *  Le magnetometre
 *
 *
 *  Pin arduino utilisés
 *  Pin 20 = SDA
 *  Pin 21 = SCL
 *  Pin 14 = Rx GPS
 *  Pin 15 = Tx GPS
 *  Pin 6 = Servo direction
 *  Pin 7 = Servo vitesse.
 *  Pin 8 = bouton home.
 *
 *  _________________________________________
 *  Jean-Paul Cano ( 2017)
 *  Version : 1.0
 *
 *
 *
*/

#include "Glider_cart.h"


void setup()
{
  pinMode( pin_home, INPUT);
  pinMode(pin_dir, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(4800);                                                  // Serial port for GPS
  Serial.println("return Home RC Glider take off cart, Version 2.0");
  Wire.begin();

}


void loop()
{

  while (Serial1.available() > 0)
    gps.encode(Serial1.read());
    delay(10);
  int x=0;
  while (Serial.available())
    Command[x++]=Serial.read();                                           //lit une chaine de caractere sur le port serie et la stocke dans une variable string.
    delay(10);
  
    
/* Capturing and saving home postion */
    
    if(Command == "home")
    {
      Serial.println("homing");
      delay(2000);
      HomeLat = gps.location.lat();
      HomeLng = gps.location.lng();
      Command = "null";
    }

  if (gps.location.isValid())                                              //debogage fonction fix
    fix = "Fix Ready";
  else
    fix = "wait fix";

  if (gps.location.isUpdated())                                            // Lit les données et calcule le cap a prendre et la distance a parcourir
  {                                                                        //calcule distance a parcourir vers home.
    distHome = gps.distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      HomeLat,
      HomeLng);

    courseHome = gps.courseTo(                                            // Calcule cap vers home;
      gps.location.lat(),
      gps.location.lng(),
      HomeLat,
      HomeLng);


  Serial.print("Dist: ");                                                 // Impressions pour debogage.
  Serial.print(distHome);
  Serial.print("\t");
  Serial.print("Course Home: ");
  Serial.print(courseHome);
  Serial.print("\t");
  Serial.print("heading: ");
  Serial.print(headingDeg());
  Serial.print("\t");
  Serial.print( fix );
  Serial.print("\t");
  Serial.print("speed: ");
  Serial.println(gps.speed.mps());


  }

  if (digitalRead (pin_home) == HIGH)                 // Check if return home pin activated.
  {                                                   // routine retour home en cours d'etude....

 // check for GPS position update, calculate course and distance.
     
    if (gps.location.isUpdated())                  
    {                                               
    distHome = gps.distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      HomeLat,
      HomeLng);

    courseHome = gps.courseTo(                                      
      gps.location.lat(),
      gps.location.lng(),
      HomeLat,
      HomeLng);
    }
    
    if(distHome > 0.1)
    {
      servo(motorSpeed, turnRight, pin_vit);                            // motor speed.
      headingMag = headingDeg();                           // Heading form magnetometer from function headingDeg

      diffAngle = abs(courseHome - headingMag);
      
// Call direction function for shortest turn

      droite(headingMag, courseHome, &turnRight);

      if (diffAngle > 180.0)
        diffAngle = 360.0 - diffAngle;

// Console printing for debugging

        Serial.print ("diff_angle \t");
        Serial.print (diffAngle);
        Serial.print ("\t");
        if (turnRight)
          Serial.println("droite");
        else
          Serial.println("gauche");

/*funtion to rotate servo
based on  difference between course and heading*/

    servo (diffAngle, turnRight, pin_dir);           

    }

  }

}


