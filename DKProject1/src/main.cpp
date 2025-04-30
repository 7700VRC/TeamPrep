/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*          February lessons */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LM                   motor         1
// RM                   motor         2
// Gyro                 inertial      3
// Lift                 motor         8
// Claw                 motor         9
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
// Custom Function---------//
float D = 4.0; // wheel diameter
float Pi = 3.14;
void drive(int lspeed, int rspeed, int wt) {
  LM.spin(fwd, lspeed, pct);
  RM.spin(fwd, rspeed, pct);
  wait(wt, msec);
}

void driveBrake() {
  LM.stop(brake);
  RM.stop(brake);
}

void inchDrive(float target) {
  float x = 0.0;
  LM.setPosition(0.0, rev);
  while (x < target) {
    drive(50, 50, 10);
    x = LM.position(rev) * Pi * D;
  }
  driveBrake();
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
  Brain.Screen.printAt(1, 20, "Auton is running");
  wait(500, msec);
  drive(50, 50, 1000);
  driveBrake();
  wait(500, msec);
  inchDrive(24);
  Brain.Screen.clearScreen();
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
  while (true) {
    drive(Controller1.Axis3.position(pct), Controller1.Axis2.position(pct), 10);

    if (Controller1.ButtonL1.pressing()) {
      Lift.spin(fwd, 50, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      Lift.spin(fwd, -50, pct);
    } else {
      Lift.stop(brake);
    }

       if (Controller1.ButtonR1.pressing()) {
     Claw.spin(fwd, 50, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Claw.spin(fwd, -50, pct);
    } else {
      Claw.stop(brake);
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
