/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Ashlee Hart and Emily Raventos
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
   if (radians >= (M_PI * 2.0))
   {
      double multiples = floor(radians / (M_PI * 2.0));

      return radians - ((M_PI * 2.0) * multiples);
   }

   else if (radians < 0.0)
   {
      double multiples = ceil(-radians / (M_PI * 2.0));
      return (M_PI * 2.0) * multiples + radians;
   }

   return radians;
}

/******************************************
 * SET DEGREES
 *****************************************/
void Angle::setDegrees(double degrees)
{
   setRadians(convertToRadians(degrees));
}

/******************************************
 * DIRECTION :  CONVERT TO DEGREES
 * Convert radians to degrees:
 *     radians / 2pi = degrees / 360
 *****************************************/
double Angle::convertToDegrees(double radians) const
{
   return radians / (2.0 * M_PI) * 360.0;
}

/******************************************
 * DIRECTION : CONVERT TO RADIANS
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 *****************************************/
double Angle::convertToRadians(double degrees) const
{
   return (degrees / 360.0) * 2.0 * M_PI;
}

/******************************************
 * REVERSE DIRECTION METHOD
 *****************************************/
void Angle::reverse()
{
   radians = normalize(radians + M_PI);
}

/******************************************
 * ADD RADIANS TO ANGLE
 *****************************************/
void Angle::addRadians(double radians)
{
   this->radians += radians;
   // normalize(radians);
}