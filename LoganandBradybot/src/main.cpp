/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/16/2025, 1:11:02 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller;
motor LM(PORT10, ratio18_1, true);
motor RM(PORT14, ratio18_1, false);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void test(int time, double speed)
{
  LM.spin(forward, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, msec);
  LM.stop();
  RM.stop();
}

void pre_auton(void)
{


}



void autonomous(void)
{
  test(2000, 100.0);
  test(2000, 50.0);
}


/// @brief
/// @param
void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    Brain.Screen.printAt(10, 25, "I dont care about berings and stuff.-Brady");
    Brain.Screen.printAt(10, 50, "Thats crazy.-Logan");
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawCircle(240, 136, 20);
    int Lspeed1 = Controller.Axis2.position(pct);
    int Rspeed1 = Controller.Axis3.position(pct);
    LM.spin(fwd, Lspeed1, pct);
    RM.spin(fwd, Rspeed1, pct);


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
