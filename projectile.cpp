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
 #include "acceleration.h"

 using namespace std;


 /********************************************************************
 * FIRE
 ********************************************************************/
 void Projectile::fire(const Position& posHowitzer,
    double simulationTime,
    double angle,
    //const Angle& elevation,
    double muzzleVelocity) 
 {
   reset();

   PositionVelocityTime pvt;
   pvt.pos = posHowitzer;
   pvt.t = simulationTime;
   pvt.v.setA(angle, muzzleVelocity);
   flightPath.push_back(pvt);
   cout << angle;

 }
//  void Projectile::fire(const Position& posHowitzer,
//   double simulationTime, Angle& elevation, double muzzleVelocity)
//  {
//    // clear the flight path
//    reset();
   
//    // create an initial position
//    PositionVelocityTime pvt;  
//    pvt.pos = posHowitzer;  
//    // pvt.v = Velocity(elevation, muzzleVelocity); 
//    pvt.v.set(elevation, muzzleVelocity);
//    pvt.t = simulationTime;   
//    flightPath.push_back(pvt);  

//    // launchPos = posHowitzer;
//   }

//  void Projectile::fire(const Position& initialPosition, double simulatorTime,
//     double angle, double muzzleVelocity) {
//     double vx = 0.0;
//     double vy = 0.0;
//     if (angle == 90 || angle == -90)
//     {
//        vx = muzzleVelocity;
//     }
//     if (angle == 0)
//     {
//        vy = muzzleVelocity;
//     }
//     // find position x,y
//     double posX = initialPosition.getMetersX();
//     double posY = initialPosition.getMetersY();
//     // Create a PositionVelocityTime object with the provided position, initial velocity, and simulator time
//     PositionVelocityTime pvt;
//     pvt.pos.setMetersX(posX);
//     pvt.pos.setMetersY(posY);
//     pvt.v.setDX(vx);
//     // pvt.v.setDY(vy); 
//     pvt.v.setDY(vy);
//     pvt.t = simulatorTime;

//     // Add the object to the beginning of the flight path list
//     flightPath.push_front(pvt);
//  }



 /*************************************************
 * PROJECTILE: ADVANCE
 * Advance the projectile by one time unit
 **************************************************/
 void Projectile::advance(double simulationTime)
 {
   // cout << flightPath.size() << endl;
    if (!flying())
       return; 

    // previous speed is the last one
    PositionVelocityTime pvt = flightPath.back();
    Angle angleGravity; 
    angleGravity.setDown(); 
    double speed = pvt.v.getSpeed();
    double altitude = pvt.pos.getMetersY();
    double interval = simulationTime - currentTime();    
    //cout << simulationTime << "," << currentTime() << endl;
   
    assert(interval > 0.0);

    double density = densityFromAltitude(altitude);
    double speedSound = speedSoundFromAltitude(altitude);
    double mach = speed / speedSound;
    double dragCoefficient = dragFromMach(mach);
    double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
    double accelerationDrag = accelerationFromForce(windResistance, mass); 
    double velocityWind = (velocityFromAcceleration(accelerationDrag, TIME_INCREMENT));
    Acceleration aWind(pvt.v.getAngle(), accelerationDrag); 
    pvt.v.addDY(velocityWind); 

    //double magnitudeGravity = gravityFromAltitude(altitude);
    
    //Acceleration aGravity(angleGravity, magnitudeGravity);
    double accelerationGravity = gravityFromAltitude(altitude); 
    double velocityGravity = (velocityFromAcceleration(accelerationGravity, TIME_INCREMENT));
    pvt.v.addDY(velocityGravity);   // Remove -?
    double angle = pvt.v.getAngle();

    cout << "Speed: " << speed << " Alt: " << altitude << " Interval: " << interval << " Dens: " << density << " Sound: " << speedSound;
    cout << " Mach: " << mach << " DC: " << dragCoefficient << " Wind: " << windResistance << " ADrag: " << accelerationDrag;
    cout << " VWind: " << velocityWind << " aGrav: " << accelerationGravity << " vGrav: " << velocityGravity << " Angle: " << angle << endl;
    // compute total acceleration
    //Acceleration aTotal = aGravity + aWind; 
    pvt.pos.addMetersX(velocityFromAcceleration(pvt.v.getDX(), TIME_INCREMENT));
    pvt.pos.addMetersY(velocityFromAcceleration(pvt.v.getDY(), TIME_INCREMENT));
    // Print X & Y, Figure out why speed is increasing. 
    cout << "X: " << pvt.pos.getMetersX() << " Y: " << pvt.pos.getMetersY() << endl;
    // update time
    pvt.t += TIME_INCREMENT; ////////////////////////////////////////////////////////////////////////////////// = not +=

    // remove the oldest pvt when we reach 20
    if (flightPath.size() > 19)
       flightPath.pop_front();

    // add it to the back of the flight path
    flightPath.insert(flightPath.end(), pvt);


 }