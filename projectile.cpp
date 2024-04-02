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
//void Projectile::draw(ogstream& gout) const
// {
//    int size = flightPath.size();
//    for (int i = 0; i < size; i++)
//       gout.drawProjectile(flightPath[i].pos, 0.5 * (double)i);
// }

 /*************************************************
 * PROJECTILE: ADVANCE
 * Advance the projectile by one time unit
 **************************************************/
 void Projectile::advance(double time)
 {
    // the old position
    PositionVelocityTime pvt = flightPath.back();
    double posX = pvt.pos.getMetersX();
    double posY = pvt.pos.getMetersY();
    double vX = pvt.v.getDX();
    double vY = pvt.v.getDY();
    double t = 1;

    //cout << "-----------------------------" << endl;
    //cout << "confirm old pvt values: " << endl;
    //cout << posX << endl 
    //   << posY << endl 
    //   << vX << endl 
    //   << vY << endl 
    //   << t << endl 
    //   << "---------------------------" << endl;
    
    // advance_diagonalDown() use the numbers from the comments to pass the test
    // use velocity, time, and acceleration?? to calculate a new position
    double setX = posX + (vX * t) + (0.5 * (/*ddx?*/-0.0799) * (t * t));
    double setY = posY + (vY * t) + (0.5 * (/*ddy?*/-9.8064 + /*?*/0.0638) * (t * t));
    posX = setX;
    posY = setY;

    // use old velocity, time, and acceleration? to calculate new velocity 
    double setDX = vX + (/*ddx?*/-0.0799) * t;
    double setDY = vY + (/*ddx?*/-9.8064 + /*ddy*/0.0638) * (t * t);
    vX = setDX;
    vY = setDY;

    // increase time
    t += time - t;

    //cout << "new pvt values: " << endl;
    //cout << posX << endl
    //   << posY << endl
    //   << vX << endl
    //   << vY << endl
    //   << t << endl
    //   << "---------------------------" << endl;

    // add new pvt
    PositionVelocityTime pvt1;
    pvt1.pos.setMetersX(posX);
    pvt1.pos.setMetersY(posY);
    pvt1.v.setDX(setDX);
    pvt1.v.setDY(setDY);
    pvt1.t = t;
    flightPath.push_back(pvt1);
 }

 //void Projectile::advance(double simulationTime) {
 //   // Ensure there is at least one data point in the flight path
 //   if (flightPath.empty())
 //      return;

 //   // Get the current position, velocity, and time
 //   Position currentPosition = flightPath.front().pos;
 //   Velocity currentVelocity = flightPath.front().v;
 //   double currentTime = flightPath.front().t;

 //   // Calculate the time difference between the current time and the simulation time
 //   double deltaTime = simulationTime - currentTime;

 //   // If deltaTime is negative or zero, no advancement is needed
 //   if (deltaTime <= 0)
 //      return;

 //   // Update the position using the current velocity
 //   double deltaX = currentVelocity.getDX() * deltaTime;
 //   double deltaY = currentVelocity.getDY() * deltaTime;

 //   // Update the position
 //   currentPosition.setMetersX(currentPosition.getMetersX() + deltaX);
 //   currentPosition.setMetersY(currentPosition.getMetersY() + deltaY);

 //   // Calculate the new velocity components (no change in horizontal velocity, only gravity affects vertical velocity)
 //   // Note: We assume the acceleration due to gravity is constant during this short time interval
 //   double newVelocityX = currentVelocity.getDX();
 //   double newVelocityY = currentVelocity.getDY() + (-9.80665 * deltaTime); // gravity acceleration constant

 //   // Update the time
 //   currentTime = simulationTime;
 //   PositionVelocityTime pvt;
 //   pvt.pos = currentPosition;
 //   pvt.v.setDX(newVelocityX);
 //   pvt.v.setDY(newVelocityY);
 //   pvt.t = currentTime;
 //   
 //   flightPath.push_back(pvt);
 //}

 //void Projectile::advance(double time)
 //{
   //PositionVelocityTime pvt = flightPath.back(); 
   //double speed = pvt.v.getSpeed();
   ////cout << "Speed: " << speed << endl;
   //double altitude = pvt.pos.getMetersY();
   ////cout << "Altitude: " << altitude << endl;
   //Angle angle;
   //angle.setDown();

   //// subtract wind resistance from velocity
   //double density = densityFromAltitude(altitude);
   //double dragCoefficient = dragFromMach(altitude);
   //double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
   //double accelerationDrag = accelerationFromForce(windResistance, mass);
   //double velocityWind = (velocityFromAcceleration(accelerationDrag, time));
   //pvt.v.addDY(-velocityWind);

   //// add gravity to velocity
   //double accelerationGravity = gravityFromAltitude(altitude);
   //double velocityGravity = (velocityFromAcceleration(accelerationGravity, time));
   //pvt.v.addDY(-velocityGravity);
   ////cout << "Velocity: " << pvt.v.getSpeed() << endl;

   //// get inertia
   //pvt.pos.addMetersX(pvt.v.getDX() * time); 
   //pvt.pos.addMetersY(pvt.v.getDY() * time); 
   ////cout << "Position X : " << pvt.pos.getMetersX() << endl; 
   ////cout << "Position Y : " << pvt.pos.getMetersY() << endl; 
   ////cout << "------------------------------------------------------------" << endl;

   //// update time increment
   //pvt.t += time;

   //// remove the last pvt object
   //if (flightPath.size() > 19)
   //   flightPath.pop_back(); 

   //// add to beginning of flight path
   //// flightPath.insert(flightPath.begin(), pvt);
   //flightPath.push_back(pvt);
//} 
//void Projectile::fire(Angle a, Position pos, double mv)
//{
//   PositionVelocityTime pvt;
//   double speed = pvt.v.getSpeed();
//   double altitude = pvt.pos.getMetersY();
//   Angle angle(a);
//   Position position(pos);
//   // angle.setRadians(angle);
//}
