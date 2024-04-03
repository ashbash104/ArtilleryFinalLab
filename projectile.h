/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    Brother Helfrich, Ashlee Hart, and Emily Raventos
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 


 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;
   void draw(ogstream& gout) const; 
   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {}

   // advance the round forward until the next unit of time
   void advance(double simulationTime); 

   // based on the test case titles, we should also have:
   // void reset(Projectile proj) {proj.flightPath = {}; 
   //                              proj.mass = DEFAULT_PROJECTILE_WEIGHT; 
   //                              proj.radius = DEFAULT_PROJECTILE_RADIUS;}
   void reset() {Projectile p; this->mass = p.mass; this->radius = p.radius; this->flightPath = p.flightPath;} 
   // void fire(Angle angle, Position position, double muzzleVelocity); // I think this should take the angle, position, and muzzleVelocity of the howitzer and add a PositionVelocityTime
   

   /********************************************************************
   * Move this to .cpp file
   ********************************************************************/
   void fire(const Position& initialPosition, double simulatorTime,
              double angle, double muzzleVelocity) {
        // Calculate initial velocity components based on angle and muzzle velocity
      double vx = 0.0;
      double vy = 0.0;
      if (angle == 90 || angle == -90)
      {
         vx = muzzleVelocity;
      }
      if (angle == 0)
      {
         vy = muzzleVelocity;
      }
        // find position x,y
        double posX = initialPosition.getMetersX();
        double posY = initialPosition.getMetersY();

        // Create a PositionVelocityTime object with the provided position, initial velocity, and simulator time
        PositionVelocityTime pvt; 
        pvt.pos.setMetersX(posX);
        pvt.pos.setMetersY(posY); 
        pvt.v.setDX(vx);
        pvt.v.setDY(vy); 
        pvt.t = simulatorTime;        

        // Add the object to the beginning of the flight path list
        flightPath.push_front(pvt);
    }
    double getSpeed() ///////////// to get velocity from the flightPath
    {
      double dx = flightPath.front().v.getDX();
      double dy = flightPath.front().v.getDY();
       
      return sqrt((dx * dx) + (dy * dy));
    }

    list<Position> displayPositions(list<Position> positions)
    {
       //for (double i = 0; i <= positions.size(); i++)
       //{
       //   flightPath[i].setPixelsX((double)i * 2.0);
       //   flightPath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
       //}

       //// Iterate over the list using an iterator
       //int i = 0;
       //for (auto it = flightPath.begin(); it != flightPath.end(); ++it) {
       //   it->pos.setPixelsX(static_cast<double>(i) * 2.0);
       //   ++i;
       //   it->pos.setPixelsY(500.0 / 1.5);
       //}

    }
   
private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   Position defaultPosition; // Where the projectile begins. 
   std::list<PositionVelocityTime> flightPath;
};