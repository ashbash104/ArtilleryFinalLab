/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    Ashlee Hart and Emily Raventos
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"


#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s


class TestHowitzer;

 /*********************************************
  * Howitzer
  * Everything we need to know about a howitzer (aka the gun)
  *********************************************/
class Howitzer
{
   public:
      // for unit tests
      friend ::TestHowitzer;

      // default constructor
      Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45.0) {}

      // draw
      void draw(ogstream& gout, double flightTime) const;

      // where is the howitzer at right now?
      Position & getPosition() { return position; }

      // generate a new position for the howitzer
      void generatePosition(const Position& posUpperRight);

      // get the muzzle velocity
      double getMuzzleVelocity() const { return muzzleVelocity; }

      // move the angle of the howitzer
      void rotate(double radian) { elevation.add(radian); }

      // raise (or lower) the howitzer
      void raise(double radian) {elevation.addRadians(elevation.isRight() ? -radian : radian);}

      // get the elevation
      const Angle & getElevation() const { return elevation; }

   private:
      Position position;      // initial position of the projectile
      double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
      Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
};