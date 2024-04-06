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
   //Ground ground;  
   //Position pos(10.0, pSimulator->ptUpperRight.getPixelsY() - 20.0); 
   ogstream gout(pSimulator->ptUpperRight);
   //Velocity v;
   //Angle a;

   //
   // accept input
   //

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

   // fire that gun
   if (pUI->isSpace())
   {
      pSimulator->time = 0.1;
      pSimulator->proj.fire(pSimulator->ptHowitzer, pSimulator->time, pSimulator->angle, DEFAULT_MUZZLE_VELOCITY);
      cout << pSimulator->angle << endl;
      pSimulator->time += 0.1;
   }
   

   //
   // perform all the game logic
   pSimulator->proj.advance(pSimulator->time);

   // advance time by half a second.
   pSimulator->time += TIME_INCREMENT;


   //
   // draw everything
   //

   // Velocity v(proj.flightPath.front().v.getDX(), proj.flightPath.front().v.getDY());

   // draw the ground first
   pSimulator->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pSimulator->ptHowitzer, pSimulator->angle, pSimulator->time);
   // Draw the text?
   //gout.drawText()

   // draw the projectile
   pSimulator->proj.draw(gout);
  /* for (int i = 0; i < 20; i++)
      gout.drawProjectile(pSimulator->projectilePath[i], 0.5 * (double)i); */


   // Create new position and gout to show on right?
   Position posStats(26000.0, pSimulator->ptUpperRight.getPixelsY() + 23000.0);
   ogstream goutStats(posStats);
   // draw some text on the screen
   goutStats.setf(ios::fixed | ios::showpoint); 
   goutStats.precision(1); 
   goutStats << "Altitude: "
      << pSimulator->ground.getElevationMeters(pSimulator->ptUpperRight) 
      << endl;
   goutStats << "Speed: "
      //<< proj.getSpeed()
      << endl; 
   goutStats << "Distance: "
      // << 
      << endl;
   goutStats << "Hang Time: "
      << pSimulator->time << "s\n";
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



