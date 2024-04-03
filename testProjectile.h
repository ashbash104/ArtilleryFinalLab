/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    Brother Helfrich, Ashlee Hart, and Emily Raventos
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "projectile.h"
#include "unitTest.h"
#include <vector>
#include <list>

using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      //// Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal(); 
      //advance_up(); 
      //advance_diagonalUp();
      advance_diagonalDown(); 

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      // setup
      Projectile p;

      // verify
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
      // setup
      Projectile p;
      p.mass = -99.99;
      p.radius = 99.99;
      p.flightPath = {};

      // exercise
      p.reset();

      // verify
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assert(p.flightPath.empty());
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
      // setup
      Position pos;
      Projectile p;
      p.mass = -99.99;
      p.radius = 99.99;
      Projectile::PositionVelocityTime pvt;
      p.flightPath = {};
      // exercise
      pvt.pos.x = 0.0;
      pvt.pos.y = 0.0;
      pvt.v.dx = 1.0;
      pvt.v.dy = 1.0;
      pvt.t = 2.0;
      p.flightPath.push_back(pvt);
      
      // exercise
      p.reset();

      // verify
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assert(p.flightPath.empty());
   }


   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/  

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      // setup
      Projectile p;
      Angle a;
      a.radians = 90;
      Position po;
      po.x = 111;
      po.y = 222;
      double muzzleVelocity = 100; 
      double time = 1;
      // exercise
      p.fire(po, time, a.radians, muzzleVelocity);
      // Projectile::PositionVelocityTime pvt1 = p.flightPath.begin();
      // verify
      assertEquals(p.flightPath.front().pos.x, 111.0);   
      assertEquals(p.flightPath.front().pos.y, 222.0);   
      assertEquals(p.flightPath.front().v.dx, 100.0); 
      assertEquals(p.flightPath.front().v.dy, 0.0); 
      assertEquals(p.flightPath.front().t, 1.0); 
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=-100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      // setup
      Projectile p;
      Angle a;
      a.radians = -90;
      Position po;
      po.x = 111;
      po.y = 222;
      double muzzleVelocity = -100; 
      double time = 1;
      // exercise
      p.fire(po, time, a.radians, muzzleVelocity);
      // Projectile::PositionVelocityTime pvt1 = p.flightPath.begin();
      // verify
      assertEquals(p.flightPath.front().pos.x, 111.0);   
      assertEquals(p.flightPath.front().pos.y, 222.0);   
      assertEquals(p.flightPath.front().v.dx, -100.0); 
      assertEquals(p.flightPath.front().v.dy, 0.0); 
      assertEquals(p.flightPath.front().t, 1.0);    
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      // setup
      Projectile p;
      Angle a;
      a.radians = 0;
      Position po;
      po.x = 111;
      po.y = 222;
      double muzzleVelocity = 100; 
      double time = 1;
      // exercise
      p.fire(po, time, a.radians, muzzleVelocity);
      // Projectile::PositionVelocityTime pvt1 = p.flightPath.begin();
      // verify
      assertEquals(p.flightPath.front().pos.x, 111.0);   
      assertEquals(p.flightPath.front().pos.y, 222.0);   
      assertEquals(p.flightPath.front().v.dx, 0.0); 
      assertEquals(p.flightPath.front().v.dy, 100.0); 
      assertEquals(p.flightPath.front().t, 1.0);    
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/ 

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      // setup
      Projectile p;
      // exercise
      // verify
      assert(p.flightPath.empty());
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
      // setup
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      // exercise
      pvt.pos.x = 100;
      pvt.pos.y = 200.0;
      pvt.v.dx = 0.0;
      pvt.v.dy = 0.0;
      // verify
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 100.0);
         assertEquals(p.flightPath.back().pos.y, 195.0968); 
         assertEquals(p.flightPath.back().v.dx, 0.0);
         assertEquals(p.flightPath.back().v.dy, -9.8);
         assertEquals(p.flightPath.back().t, 101.0);
      }
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      // setup
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      // exercise
      pvt.pos.x = 100;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = 0.0;
      pvt.t = 100.0;
      // verify
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9756);
         assertEquals(p.flightPath.back().pos.y, 195.0968);
         assertEquals(p.flightPath.back().v.dx, 49.9513);
         assertEquals(p.flightPath.back().v.dy, -9.8064);
         assertEquals(p.flightPath.back().t, 101.0);
      }
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
       cout << "advance_up: " << endl;
      // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 0.0;
      pvt.v.dy = 100.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      //cout << "before advance: " << endl;
      //cout << p.flightPath.back().pos.x << endl;
      //cout << p.flightPath.back().pos.y << endl;
      //cout << p.flightPath.back().v.dx << endl;
      //cout << p.flightPath.back().v.dy << endl;
      //cout << p.flightPath.back().t << endl;
      p.advance(101.0);
      //cout << "after advance: " << endl;
      //cout << p.flightPath.back().pos.x << endl;
      //cout << p.flightPath.back().pos.y << endl;
      //cout << p.flightPath.back().v.dx << endl;
      //cout << p.flightPath.back().v.dy << endl;
      //cout << p.flightPath.back().t << endl;

      //cout << " ------------------" << endl;
      //cout << "should be: " << endl
      //   << 100.00 << endl
      //   << 294.9021 << endl
      //   << 0.0 << endl
      //   << 89.8042 << endl
      //   << 101 << endl;
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 100.0);
         assertEquals(p.flightPath.back().pos.y, 294.9021);
         assertEquals(p.flightPath.back().v.dx, 0.0);
         assertEquals(p.flightPath.back().v.dy, 89.8042);
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      // cout << "advance_diagonalUp: " << endl;
      // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = 40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9201);
         assertEquals(p.flightPath.back().pos.y, 230.1297);
         assertEquals(p.flightPath.back().v.dx, 49.9201);
         assertEquals(p.flightPath.back().v.dy, 30.1297);
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }
   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {  // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9601); // 100 + 50*1 + .5(-0.0799)*1*1 --> posX + (vX * t) + (0.5 * (-0.0799) * (t * t))
         assertEquals(p.flightPath.back().pos.y, 155.1287); // 200 +-40*1 + .5(-9.8064+0.0638)*1*1 --> posY + (vy * t) + (0.5 * () * (t * t))
         assertEquals(p.flightPath.back().v.dx, 49.9201);   // 50 + (-0.0799)*1 --> vX + (-0.0799) * t
         assertEquals(p.flightPath.back().v.dy, -49.7425);  //-40 + (-9.8064+0.0638)*1*1 --> vY + (-9.8064+0.0638) * (t * t)
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};

