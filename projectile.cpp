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
    const Angle& elevation,
    double muzzleVelocity) 
 {
    reset();

    PositionVelocityTime pvt;
    pvt.pos = posHowitzer;
    pvt.t = simulationTime;
    pvt.v.set(elevation, muzzleVelocity);
    flightPath.push_back(pvt);
 }


 /*************************************************
 * PROJECTILE: ADVANCE
 * Advance the projectile by one time unit
 **************************************************/
 void Projectile::advance(double simulationTime)
 {
    if (!flying())
       return; 

    // previous speed is the last one
    PositionVelocityTime pvt = flightPath.back();
    double speed = pvt.v.getSpeed();
    double altitude = pvt.pos.getMetersY();
    double interval = simulationTime - currentTime(); 
    assert(interval > 0.0);

    double density = densityFromAltitude(altitude);
    double speedSound = speedSoundFromAltitude(altitude);
    double mach = speed / speedSound;
    double dragCoefficient = dragFromMach(mach);
    double windResistence = forceFromDrag(density, dragCoefficient, radius, speed);
    double magnitudeWind = accelerationFromForce(windResistence, mass);
    Acceleration aWind(-pvt.v.getAngle(), magnitudeWind);

    double magnitudeGravity = gravityFromAltitude(altitude);
    Angle angleGravity;
    angleGravity.setDown();
    Acceleration aGravity(angleGravity, magnitudeGravity);

     
    // compute total acceleration
    Acceleration aTotal = aGravity + aWind; 
     
    // update pvt
    pvt.pos.add(aTotal, pvt.v, interval);
    pvt.v.addAcceleration(aTotal, interval);
    pvt.t = simulationTime;

    // add to the back of the flight path
    flightPath.push_back(pvt);








 }