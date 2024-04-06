/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#include "ground.h"
#include "howitzer.h"
bool Simulator::hitTarget() const
{
   //// Get the position of the projectile
   //Position projectilePosition = proj.getPosition();

   //// Get the position of the target
   //Position targetPosition = ground.getTarget();

   //// Define a threshold for considering the projectile has hit the target
   //double threshold = 1.0; // Adjust as needed

   //// Check if the distance between the projectile and the target is within the threshold
   //double distance = projectilePosition.computeDistance(projectilePosition, targetPosition); 

   //return distance <= threshold;

   Position groundPos = ground.getTarget(); 

   // if we are too high
   if (proj.getAltitude() != groundPos.getMetersY())
      return false;
   // if it's too far right
   if (proj.getPositionX() > groundPos.getMetersX() + 0.077545)
      return false;
   // if it's too far left
   if (proj.getPositionX() < groundPos.getMetersX() - 0.077545)
      return false;

   // if we hit the ground
   if (proj.getPositionY() == ground.getElevationMeters(proj.getPosition())) 
      return false;

   return true;
} 

void Simulator::displayEndMessage(string endMessage)
{
   // show message and reset if hits target
   ogstream gout;
   // reset the projectile and time
   Position endText;
   endText.setMetersX(20000);
   endText.setMetersY(16000);
   gout.setPosition(endText);
   gout << endMessage;

   proj.reset();
   time = 0.0;

   needToSleep = true;
}  
// // reset
// void Simulator::reset()
// {

// }

// void Simulator::draw(ogstream& gout) const
// {
//    Ground ground; 
//    Howitzer h; 
//    gout.setf(ios::fixed | ios::showpoint);
//    gout.precision(1);
//    ground.draw(gout);
//    h.draw(gout, 0.0);
// }