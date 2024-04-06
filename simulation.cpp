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
   // Get the position of the projectile
   Position projectilePosition = proj.getPosition();

   // Get the position of the target
   Position targetPosition = ground.getTarget();

   // Define a threshold for considering the projectile has hit the target
   double threshold = 1.0; // Adjust as needed

   // Check if the distance between the projectile and the target is within the threshold
   double distance = projectilePosition.computeDistance(projectilePosition, targetPosition); 

   return distance <= threshold;
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