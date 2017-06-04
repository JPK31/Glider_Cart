
//--------------------------------------------------------
//  Calculate direction (R or L), boolean value for R
//--------------------------------------------------------
#include "direct.h"

void droite(float heading, float Route, bool *p_turn)
{

  if(Route <= 180) 
    *p_turn = (heading > Route) && (heading < Route + 180);
  else
    *p_turn = (heading > Route) || (heading < Route - 180);
  
}

