/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "projectile.h"
using namespace std;

/*************************************************************************
 * Simulator
 *************************************************************************/
class Simulator
{
public:
   Simulator(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(0.0),
      angle(0.0)
   {
      // Set the horizontal position of the howitzer. This should be random.
      ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer); 
   }
   bool hitTarget() const; 
   bool hitGround() const;

   void displayEndMessage(string endMessage);
  /* bool hitTarget()
   {
      if (proj.getProjectilePosition() == ground.getTarget())
         return true;
      else
         return false;
   }*/

   Ground ground;                 // the ground
   Position  projectilePath[20];  // path of the projectile
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   Projectile proj;  
   double angle;                  // angle of the howitzer 
   double time;                   // amount of time since the last firing   
   bool needToSleep = false;
};
