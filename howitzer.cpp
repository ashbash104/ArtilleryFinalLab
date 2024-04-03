/***************************************************
* Source File:
 *    Lab 12: M777 Howitzer
 * Author:
 *    Ashlee Hart and Emily Raventos
 * Sources:
 *    ChatGPT
 * Summary:
 *    Howitzer
****************************************************/
#include "howitzer.h"
#include "position.h"

void Howitzer::draw(ogstream& gout, double flightTime) const
{
   gout.drawHowitzer(position,
      elevation.getRadians(),
      flightTime);
}

void Howitzer::generatePosition(const Position& posUpperRight)
{
   double xPixels = random(posUpperRight.getPixelsX() * 0.1,
      posUpperRight.getPixelsX() * 0.9);
   position.setPixelsX(xPixels);
   position.setPixelsY(0);
}