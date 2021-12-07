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
// LDrive               motor_group   1, 2            
// RDrive               motor_group   9, 10           
// LDist                distance      11              
// CDist                distance      12              
// RDist                distance      13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

void drive(int lspeed, int rspeed, int wt) {
  LDrive.spin(forward, lspeed, percent);
  RDrive.spin(forward, rspeed, percent);
  wait(wt, msec);
}

void seekObject() {
  float d = 0.5;
  float kb = 2.0;
  float L = 0.0;
  float C = 0.0;
  float R = 0.0;
  float lsp = 0.0;
  float rsp = 0.0;
  L = LDist.objectDistance(inches);
  C = CDist.objectDistance(inches);
  R = RDist.objectDistance(inches);
  while (fabs(R - L) > d) {
    L = LDist.objectDistance(inches);
    C = CDist.objectDistance(inches);
    R = RDist.objectDistance(inches);
    Brain.Screen.printAt(1, 40, "L,C,R  %.1f   %.1f   %.1f", L, C, R);
    lsp = kb * (L-R);
    rsp = kb * (R-L);
    drive(lsp, rsp, 10);
  }
  while (C > d) {
    C = CDist.objectDistance(inches);
    drive(30, 30, 10);
  }
  drive(0, 0, 0);
}

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

void autonomous(void) {}

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
  float L = 0.0;
  float C = 0.0;
  float R = 0.0;

  while (1) {
    L = LDist.objectDistance(inches);
    C = CDist.objectDistance(inches);
    R = RDist.objectDistance(inches);
    Brain.Screen.printAt(1, 40, "L,C,R  %.1f   %.1f   %.1f", L, C, R);
    //wait(2000, msec);

      //seekObject();

      int lstick=Controller1.Axis3.position(percent);
      int rstick=Controller1.Axis2.position(percent);
      drive(lstick, rstick, 10);
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
