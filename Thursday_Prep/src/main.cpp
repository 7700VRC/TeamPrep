/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      3/27/2025, 5:16:32 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//define drive motors
motor RBM = motor (PORT11, ratio18_1, true); 
motor LBM = motor (PORT12, ratio18_1, false);
motor RFM = motor (PORT3, ratio18_1, true);
motor LFM = motor (PORT2, ratio18_1, false);
//define other motors
motor INTAKE = motor (PORT4, ratio18_1, false);
motor CLAMP = motor (PORT16, ratio18_1, false);

//Define Control
controller c1;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

//drive code    
int rspeed = c1.Axis2.position (pct);
int lspeed = c1.Axis3.position (pct);
RBM.setVelocity (rspeed, pct);
RFM.setVelocity (rspeed, pct);
LBM.setVelocity (lspeed, pct);
LFM.setVelocity (lspeed, pct);

RBM.spin (forward);
RFM.spin (forward);
LBM.spin (forward);
LFM.spin (forward);

//clamp and intake
if (c1.ButtonR1.pressing ()){
  INTAKE.spin (forward, 75, pct);
}
else if(c1.ButtonR2.pressing ()){
  INTAKE.spin (forward, -75, pct);
}
else {INTAKE.stop ();}

if (c1.ButtonL1.pressing ()){
  CLAMP.spin (forward, 75, pct);
}
else if(c1.ButtonL2.pressing ()){
  CLAMP.spin (forward, -75, pct);
}
else {CLAMP.stop ();}

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
