/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Emily Raventos and Ashlee Hart
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle()                  : radians(0.0)                      {}
   Angle(const Angle& rhs)  : radians(rhs.getRadians())         {}
   Angle(double degrees)    : radians(9.9)                      {}


   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }
   bool   isRight()          const { if (this->radians > 0 && this->radians < M_PI) return true; else return false;}
   bool   isLeft()           const { if (this->radians < 0 || this->radians > M_PI) return true; else return false;}
   


   // Setters
   void setDegrees(double degrees);
   void setRadians(double radians)    { this->radians = normalize(radians); }
   void setUp()                       { setRadians(0.0); }
   void setDown()                     { setRadians(M_PI); }
   void setRight()                    { setRadians(M_PI / 2); }
   void setLeft()                     { setRadians(M_PI + M_PI_2); }
   void setDxDy(double dx, double dy) { this->radians = normalize(atan2(dx, dy)); }
   void reverse(); // in cpp
   void addRadians(double radians);                         
   Angle& add(double delta)           { this->radians = normalize(radians) + normalize(delta); return *this; }


   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   //     |/
   
   Angle operator+(double degrees) const { return Angle(); }

private:

   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
   double dx;
   double dy;
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}