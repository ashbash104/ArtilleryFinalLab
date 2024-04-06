//  /**********************************************************************
//  * Source File:
//  *    Lab 12: M777 Howitzer
//  * Author:
//  *    <your name here>
//  * Summary:
//  *    Simulate firing the M777 howitzer 15mm artillery piece
//  ************************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "simulation.h" // for SIMULATION
#include "position.h"   // for POSITION
#include "test.h"       // for the unit tests
#include "howitzer.h"
#include "ground.h"
#include "projectile.h"
#include "Windows.h" // for sleep
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSimulator = (Simulator*)p;

   ogstream gout(pSimulator->ptUpperRight);

   // Pause for user to see end message, then reset.
   if (pSimulator->needToSleep)
   {
      Sleep(2000);
      pSimulator->needToSleep = false;
      pSimulator->proj.reset();
      pSimulator->ground.reset(pSimulator->ptHowitzer);
   }

   // move a large amount
   if (pUI->isRight())
      pSimulator->angle += 0.05;
   if (pUI->isLeft())
      pSimulator->angle -= 0.05;

   // move by a little
   if (pUI->isUp())
      pSimulator->angle += (pSimulator->angle >= 0 ? -0.003 : 0.003);
   if (pUI->isDown())
      pSimulator->angle += (pSimulator->angle >= 0 ? 0.003 : -0.003);

   // fire the gun
   if (pUI->isSpace())
   {
      pSimulator->time = 0.0;
      pSimulator->proj.fire(pSimulator->ptHowitzer, pSimulator->time, pSimulator->angle, DEFAULT_MUZZLE_VELOCITY);
      //cout << pSimulator->angle << endl;
      pSimulator->time += 0.1;
   }
   
   ////////// perform all the game logic //////////
   pSimulator->proj.advance(pSimulator->time);

   // advance time by half a second.
   if (pSimulator->proj.flying())
   {
      pSimulator->time += TIME_INCREMENT; 
   }

   // check if the projectile hits the target
   if (pSimulator->ground.hitTarget(pSimulator->proj.getPosition())) 
   {
      pSimulator->displayEndMessage("You hit the target!");
   }
   // check if the projectile hits the ground
   else if (pSimulator->time > 0.1 && pSimulator->ground.hitGround(pSimulator->proj.getPosition())/*hitGround()*//*proj.getAltitude() <= 750.0*/)
   {
      pSimulator->displayEndMessage("You missed!");
   }
   // check if the projectile leaves the screen
   else if (pSimulator->time > 0.1 && (pSimulator->proj.getAltitude() >= 26000 || pSimulator->proj.getPositionX() >= 35000 || pSimulator->proj.getPositionX() <= 0.0)) // change to screen size instead of 750.0
   {
      pSimulator->displayEndMessage("You missed!");
   }

   ////////// draw everything //////////
   
   // draw the ground first
   pSimulator->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pSimulator->ptHowitzer, pSimulator->angle, pSimulator->time);

   // draw the projectile
   pSimulator->proj.draw(gout);


   //// show message and reset if hits target
   //if (pSimulator->hitTarget()) 
   //{
   //   // reset the projectile and time
   //   Position endText; 
   //   endText.setMetersX(20000); 
   //   endText.setMetersY(16000); 
   //   gout.setPosition(endText); 
   //   gout << "You hit the target!"; 
   //   needToSleep = true;

   //   pSimulator->proj.reset(); 
   //   pSimulator->time = 0.0; 
   //}

   //// show message and reset if hits ground
   //else if (pSimulator->time > 0.1 && pSimulator->proj.getAltitude() <= 750.0) // change to ground level instead of 0.0
   //{
   //   // reset the projectile and time
   //   Position endText; 
   //   endText.setMetersX(20000);
   //   endText.setMetersY(16000); 
   //   gout.setPosition(endText);
   //   gout << "You missed!";

   //   pSimulator->proj.reset(); 
   //   pSimulator->time = 0.0; 

   //   needToSleep = true;


   //   // reset the ground
   //   //pSimulator->ground.reset(pSimulator->ptHowitzer); 
   //}

    // Create new position and gout to show on right?
   Position posStats(28500.0, pSimulator->ptUpperRight.getPixelsY() + 22500.0);
   ogstream goutStats(posStats);
   // draw some text on the screen
   goutStats.setf(ios::fixed | ios::showpoint); 
   goutStats.precision(1); 
   if (pSimulator->proj.flying())
   {
      goutStats << "Altitude: "
         << pSimulator->proj.getAltitude()
         << "m"
         << endl;
      goutStats << "Speed: "
         << pSimulator->proj.getSpeed()
         << "m/s"
         << endl;
      //goutStats << "Total Distance: "
      //   // This uses the pathagorean theorum to find the hypotonuse between the howitzer and projectile
      //   << pSimulator->ptUpperRight.computeDistance(pSimulator->proj.getPosition(), pSimulator->ptHowitzer) // doesn't start at 0 because I can't check if it's flying in position
      //   << endl;
      goutStats << "Distance: "
         // This finds the absolute value horizontal distance between the howitzer and the projectile
         << pSimulator->proj.computeProjectileDistance(pSimulator->proj.getPosition(), pSimulator->ptHowitzer)
         << "m"
         << endl;
      goutStats << "Hang Time: "
         << pSimulator->time << "s\n";
   }
   else
   {
      goutStats << "Angle: "
         << pSimulator->angle
         << "degree"
         << endl;
   }

   // bool hitTarget() 
   // {
   //    if (pSimulator->proj.getProjectilePosition() == pSimulator->ground.getTarget())
   //    {
   //       return true;
   //    }
   // }

   // change status and end when hits ground
   // if (pSimulator->proj.hitTarget(pSimulator->proj.getPosition(), pSimulator->proj.getRadius()))
   // {
   //    gout << "Houston, we have a problem!" << endl;
   //    lander.crash();
   //    needToSleep = true;
   // }

   // // change status and end when lands
   // if (ground.onPlatform(lander.getPosition(), LANDER_WIDTH))
   // {
   //    gout << "The Eagle has landed!" << endl;
   //    lander.land();
   //    needToSleep = true;
   // }
   // if (pSimulator->proj.getAltitude() == 0.0) //pSimulator->ground[pSimulator->proj.getPositionX()])
   // {
   //    //!flying();
   //    //pSimulator->proj.flying() = false;
   //    pSimulator->proj.reset();
   // }
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   testRunner(); 
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulator simulator(ptUpperRight);

   // set everything into action
   ui.run(callBack, &simulator);
   //Projectile proj;
   //proj.displayPositions();

   return 0;
}



