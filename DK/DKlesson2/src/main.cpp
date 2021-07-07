/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Rolling Robots                                                      */
/*    Created:      May 8 2021  Updated: May 15,2021                                        */
/*    Description:  Competition Lesson1                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1               
// RightMotor           motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt)
{
  LeftMotor.spin(forward, lspeed, percent);
   RightMotor.spin(forward, rspeed, percent); 
   wait(wt,msec);
}

// Add an inchDrive function to move the robot a specific number of inches
// --  need to know how far the robot will move for one turn of the wheel
// --  create global variable for wheel diameter or circumference
// --  monitor encoder on one or both wheels until they have moved a target number of inches
/////////////////


// Add a Rotate function that uses encoders to rotate the robot a set number of degrees.
//  -- robot will rotate when one side runs backwards and the other forward
//  -- use encoders to set how much the robot will rotate
//  -- need some math of basic geometry of circles
//  -- will need to know the track width of the drive base
//  -- save it in a global variable
///////////////

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
float turns=0.0;
Brain.Screen.printAt(0, 20, "Pre auton is running");

/////////////  should move this to auton   /////////
turns=LeftMotor.position(rev);
Brain.Screen.printAt(0, 40, "Turns = %0.3f",turns);
drive(50, 50, 1000);
drive(0,0,0);
turns=LeftMotor.position(rev);
Brain.Screen.printAt(0, 60, "Turns = %f",turns);
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
