/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    Ashlee Hart, Emily Raventos
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>



/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & a, double magnitude)
{
   ddx = sin(a.getRadians()) * magnitude;  // Does this need to be negative?
   ddy = cos(a.getRadians()) * magnitude;
}
void AccelerationDummy::set(const Angle& a, double magnitude)
{
   assert(false);
}

/*********************************************
  * ACCELERATION : ADD
  *  a += a
  *********************************************/
void Acceleration::addAcceleration(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}
