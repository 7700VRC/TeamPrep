/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftMotor            motor         19              
// RightMotor           motor         9               
// Roller               motor         16              
// ColorSensor          optical       6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

bool Red = true;
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt) {
  LeftMotor.spin(forward, lspeed, pct);
  RightMotor.spin(forward, rspeed, pct);
  wait(wt, msec);
}

void turnRoller() {
  int colorR = ColorSensor.value();
  drive(10, 10, 10);
      Brain.Screen.printAt(1, 40, "color value = %d  ",colorR);
  if (Red == true) {
    while (colorR < 150) {
      ColorSensor.setLightPower(100);
      Roller.spin(forward, 100, percent);
      colorR = ColorSensor.value();
      Brain.Screen.printAt(1, 40, "color value = %d  ",colorR);
    }
    Roller.stop();

  } else {
    while (colorR > 50) {
      Roller.spin(forward, 70, percent);
      colorR = ColorSensor.value();
    }
    Roller.stop();
  }
   ColorSensor.setLightPower(0);
  drive(0, 0, 0);
}
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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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
  Controller1.ButtonA.pressed(turnRoller);
  while (true) {
    int lstick = Controller1.Axis3.position();
    int rstick = Controller1.Axis2.position();
    drive(lstick, rstick, 10);
    if (Controller1.ButtonR1.pressing()) {
      Roller.spin(forward, 70, pct);

    } else if (Controller1.ButtonR2.pressing()) {
      Roller.spin(forward, -70, pct);
    } else {
      Roller.spin(forward, 0, pct);
    }
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
