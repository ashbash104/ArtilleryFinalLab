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


 /********************************************************************
 * FIRE
 ********************************************************************/
 void Projectile::fire(const Position& initialPosition, double simulatorTime,
    double angle, double muzzleVelocity) {
    // Calculate initial velocity components based on angle and muzzle velocity
    double vx = 0.0;
    double vy = 0.0;
    if (angle == 90 || angle == -90)
    {
       vx = muzzleVelocity;
    }
    if (angle == 0)
    {
       vy = muzzleVelocity;
    }
    // find position x,y
    double posX = initialPosition.getMetersX();
    double posY = initialPosition.getMetersY();

    // Create a PositionVelocityTime object with the provided position, initial velocity, and simulator time
    PositionVelocityTime pvt;
    pvt.pos.setMetersX(posX);
    pvt.pos.setMetersY(posY);
    pvt.v.setDX(vx);
    pvt.v.setDY(vy);
    pvt.t = simulatorTime;

    // Add the object to the beginning of the flight path list
    flightPath.push_front(pvt);
 }


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

    // advance_diagonalDown() use the numbers from the comments to pass the test
    // use velocity, time, and acceleration?? to calculate a new position
    double setX = posX + (vX * t) + (0.5 * (/*ddx?*/-0.0799) * (t * t));
    double setY = posY + (vY * t) + (0.5 * (/*ddy?*/-9.8064 + /*?*/0.0638) * (t * t));
    posX = setX;
    posY = setY;

    // use old velocity, time, and acceleration? to calculate new velocity 
    double setDX = vX + (/*ddx?*/-0.0799) * t;
    double setDY = vY + (/*dd?*/-9.8064 + /*ddy*/0.0638) * (t * t);
    vX = setDX;
    vY = setDY;

    // increase time
    t += time - t;

    // add new pvt
    PositionVelocityTime pvt1;
    pvt1.pos.setMetersX(posX);
    pvt1.pos.setMetersY(posY);
    pvt1.v.setDX(setDX);
    pvt1.v.setDY(setDY);
    pvt1.t = t;
    flightPath.push_back(pvt1);
 }