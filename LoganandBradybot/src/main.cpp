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

void pre_auton(void)
{

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  drive(2000, 100.0);
  drive(2000, 50.0);
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/// @brief
/// @param
void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    Brain.Screen.printAt(10, 25, "LoganandBradybot is gonna dunk on u little bro");
    Brain.Screen.printAt(10, 50, "VWOOOOOOOOOMMMMMM");
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawCircle(240, 136, 20);
    int Lspeed1 = Controller.Axis2.position(pct);
    int Rspeed1 = Controller.Axis3.position(pct);
    LM.spin(fwd, Lspeed1, pct);
    RM.spin(fwd, Rspeed1, pct);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

void drive(int time, double speed)
{
  LM.spin(forward, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, msec);
  LM.stop();
  RM.stop();
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
