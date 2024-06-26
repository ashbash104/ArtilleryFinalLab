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
//#include "ground.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m
#define TIME_INCREMENT 1.0

// forward declaration for the unit test class
class TestProjectile; 

/*********************************************
 * PVT
 * A struct to represent our projectile's current
 * position, velocity, and time
 *********************************************/
struct PVT
{
   Position pos;
   Velocity vel;
   double time;
};

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT),
      radius(DEFAULT_PROJECTILE_RADIUS) {}

   //void fire(const Position& posHowitzer,
   //   double simulationTime,
   //   const Angle& elevation,
   //   double muzzleVelocity);


   void fire(const Position& posHowitzer,
      double simulationTime,
      double angle,
      //const Angle& elevation,
      double muzzleVelocity); 

   void reset()
   {
      flightPath.clear();
      mass = DEFAULT_PROJECTILE_WEIGHT;
      radius = DEFAULT_PROJECTILE_RADIUS;
   }

   void advance(double simulationTime);

   void draw(ogstream& gout) const
   {
      for (auto it = flightPath.cbegin(); it != flightPath.cend(); ++it)
      {

         gout.drawProjectile(it->pos, currentTime() - it->t); 
         //if (it->pos == )
      }
   }

   bool flying() const { return !flightPath.empty(); }

   double getAltitude() const { return flying() ? flightPath.back().pos.getMetersY() : 0; }

   Position getPosition() const { return flying() ? flightPath.back().pos : Position(); }

   double getPositionX() const { return flying() ? flightPath.back().pos.getMetersX() : 0.0; }

   double getPositionY() const { return flying() ? flightPath.back().pos.getMetersY() : 0.0; }

   double getFlightTime() const
   {
      return (flightPath.size() >= 2) ? flightPath.back().t - flightPath.front().t : 0.0;
   }

   double getFlightDistance() const
   {
      if (flying())
      {
         return (flightPath.size() >= 2) ?
            abs(flightPath.front().pos.getMetersX() - flightPath.back().pos.getMetersX()) : 0.0;
      }
   }

   inline double computeProjectileDistance(const Position& pos1, const Position& pos2)
   {
      if (flying())
      {
         return abs(pos1.getMetersX() - pos2.getMetersX());
      }
   }

   //bool hitTarget() const
   //{
   //   PositionVelocityTime pvt = flightPath.back();
   //   // if we hit the ground
   //   if (pvt.pos.getMetersY() == ground.getTarget().getMetersY() && pvt.pos.getMetersX() ==  ground.getTarget().getMetersY())
   //      return false;

   //   return true;
   //}

   //bool hitGround() const
   //{
   //   PositionVelocityTime pvt = flightPath.back();
   //   // if we hit the ground
   //   if (pvt.pos.getMetersY() == ground.getElevationMeters(pvt.pos))
   //      return false;

   //   return true;
   //}

   double getSpeed() const { return flying() ? flightPath.back().v.getSpeed() : 0.0; }

   double currentTime() const { return flying() ? flightPath.back().t : 0.0; } 

   void setMass(double mass) { this->mass = mass;} 

   void setRadius(double radius) { this->radius = radius; }

   double getRadius() const { return radius; }
   // bool hitTarget(); 

private:
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;
   double radius;
   //Ground ground;
   // Position launchPos; 
   std::list<PositionVelocityTime> flightPath; 
};