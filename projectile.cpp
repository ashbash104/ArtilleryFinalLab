/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Ashlee Hart and Emily Raventos
 * Sources:
 *    ChatGPT
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;

 /*********************************************
 * PROJECTILE : DRAW
 * Show the projectile on the screen
 *********************************************/
/* void Projectile::draw(ogstream& gout) const
 {
    int size = flightPath.size();
    for (int i = 0; i < size; i++)
       gout.drawProjectile(flightPath[i].pos, 0.5 * (double)i);
 }*/ 

 /*************************************************
 * PROJECTILE: ADVANCE
 * Advance the projectile by one time unit
 **************************************************/
 void Projectile::advance(double time)
 {
   PositionVelocityTime pvt = flightPath.back(); 
   double speed = pvt.v.getSpeed();
   //cout << "Speed: " << speed << endl;
   double altitude = pvt.pos.getMetersY();
   //cout << "Altitude: " << altitude << endl;
   Angle angle;
   angle.setDown();

   // subtract widn resistance from velocity
   double density = densityFromAltitude(altitude);
   double dragCoefficient = dragFromMach(altitude);
   double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
   double accelerationDrag = accelerationFromForce(windResistance, mass);
   double velocityWind = (velocityFromAcceleration(accelerationDrag, time));
   pvt.v.addDY(-velocityWind);

   // add gravity to velocity
   double accelerationGravity = gravityFromAltitude(altitude);
   double velocityGravity = (velocityFromAcceleration(accelerationGravity, time));
   pvt.v.addDY(-velocityGravity);
   //cout << "Velocity: " << pvt.v.getSpeed() << endl;

   // get inertia
   pvt.pos.addMetersX(pvt.v.getDX() * time); 
   pvt.pos.addMetersY(pvt.v.getDY() * time); 
   //cout << "Position X : " << pvt.pos.getMetersX() << endl; 
   //cout << "Position Y : " << pvt.pos.getMetersY() << endl; 
   //cout << "------------------------------------------------------------" << endl;

   // update time increment
   pvt.t += time;

   // remove the last pvt object
   if (flightPath.size() > 19)
      flightPath.pop_back(); 

   // add to beginning of flight path
   // flightPath.insert(flightPath.begin(), pvt);
   flightPath.push_back(pvt);
} 
//void Projectile::fire(Angle a, Position pos, double mv)
//{
//   PositionVelocityTime pvt;
//   double speed = pvt.v.getSpeed();
//   double altitude = pvt.pos.getMetersY();
//   Angle angle(a);
//   Position position(pos);
//   // angle.setRadians(angle);
//}
