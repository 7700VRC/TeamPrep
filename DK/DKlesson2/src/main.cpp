/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Rolling Robots */
/*    Created:      May 8 2021                                          */
/*    Description:  Competition Lesson1                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1
// RightMotor           motor         2
// Controller1          controller
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
float d=3.25;  // diameter of wheel in inches
float pi=3.14;
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt) {
  LeftMotor.spin(forward, lspeed, percent);
  RightMotor.spin(forward, rspeed, percent);
  wait(wt, msec);
}

void inchDrive(float target)
{
  float inches=0.0;
  RightMotor.setPosition(0, rev);

  while(inches<=target)
  {
drive(50,50,10);
inches=RightMotor.position(rev)*pi*d;
  }
  drive(0,0,0);
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
  float turns = 0.0;
  Brain.Screen.printAt(0, 20, "Pre auton is running");
  turns = LeftMotor.position(rev);
  Brain.Screen.printAt(0, 40, "Turns = %0.3f", turns);
  drive(50, 50, 1000);
  drive(0, 0, 0);
  turns = LeftMotor.position(rev);
  Brain.Screen.printAt(0, 60, "Turns = %f", turns);
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
wait(1000, msec);
  inchDrive(27);
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
  int lspeed = 0;
  int rspeed = 0;
  // User control code here, inside the loop
  while (1) {
    /*
    lspeed = Controller1.Axis3.position();
    rspeed = Controller1.Axis2.position();
    drive(lspeed, rspeed, 10);
    */
    drive(Controller1.Axis3.position(),Controller1.Axis2.position(),10);
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
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Back to Main");
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
