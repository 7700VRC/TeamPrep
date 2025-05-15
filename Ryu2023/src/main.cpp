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
// L                    motor         1               
// R                    motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void DriveRobot(int lspeed, int rspeed, int wt){

R.spin(forward, rspeed, pct);
L.spin(forward, lspeed, pct);
wait(wt,msec);
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

void autonomous(void) {
    Brain.Screen.printAt(1,40,"Auton is running");
    DriveRobot(100, 100, 2000);
    DriveRobot(85, -85, 1000);
    DriveRobot(100, 100, 2000);
    DriveRobot(0,0,0);
    
  }

  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................


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
  while (1==1) {
  Brain.Screen.printAt(1,60,"Use the controller");
  int lspeed = Controller1.Axis3.position(pct);
  int rspeed = Controller1.Axis2.position(pct);
  DriveRobot(lspeed, rspeed, 10);
  if(Controller1.ButtonR1.pressing()){
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.drawCircle(240, 136, 20);
  }
  else if(Controller1.ButtonR2.pressing()){
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawCircle(240, 136, 10);
  }
  else {
    Brain.Screen.clearScreen();
  }
    wait(10, msec); // Sleep the task for a short amount of time to
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
