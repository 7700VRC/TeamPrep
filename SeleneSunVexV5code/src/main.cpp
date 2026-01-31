/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      1/30/2026, 4:16:59 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;


motor LF (PORT10, ratio18_1, true);
motor LB (PORT9, ratio18_1, true);
motor RF (PORT20, ratio18_1, false);
motor RB (PORT16, ratio18_1, false);

controller RC; 

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void drawonBrain () {
  
  Brain.Screen.printAt(20, 20, "Hello, World!");
  Brain.Screen.setPenWidth(10);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawCircle(240, 135, 50);

}

void RobotDrive (int Rspeed, int Lspeed, int waitTime) {

  LF.spin(forward, Lspeed, pct);
  LB.spin(forward, Lspeed, pct);
  RF.spin(forward, Rspeed, pct);
  RB.spin(forward, Rspeed, pct);
  
  wait(waitTime, msec);
}

void StopRobot (){

  LF.stop();
  LB.stop();
  RF.stop();
  RB.stop();

}


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

  RobotDrive(50, 50, 2100);
  RobotDrive(-25, 25, 550);
  StopRobot();
  RobotDrive(50, 50, 500);


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
    
    // drawonBrain();
    
    int Lspeed = RC.Axis2.position(pct);
    int Rspeed = RC.Axis3.position(pct);
    
    RobotDrive(Rspeed, Lspeed, 30);

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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
