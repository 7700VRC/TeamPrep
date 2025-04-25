/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Its A Me A Trentio                                                   */
/*    Created:      4/14/2025, 4:45:47 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;


// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor LF (PORT6, ratio6_1, true);
motor RF (PORT9, ratio6_1, false);
motor LB (PORT11, ratio6_1, true);
motor RB (PORT20, ratio6_1, false);

float dia = 3.25;
float gearRatio = 0.6;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void printscreen () {
  Brain.Screen.printAt(10, 136, "ITS A ME A TRENTIO'S ROBOT. HE IS THE RULER OF EARTH AND IS VERY SIGMA");
  Brain.Screen.printAt(240,200, "fdhjsklfhdjsqklfdhjkslfhjdkslahfjkdsahjfds");
  Brain.Screen.drawRectangle (250, 20, 15, 15);
  Brain.Screen.clearScreen ();
  wait (3, sec);
  Brain.Screen.printAt(10, 17, "ITS A ME A TRENTIO'S ROBOT. HE IS THE RULER OF EARTH AND IS VERY SIGMA");
  Brain.Screen.printAt(240,26, "fdhjsklfhdjsqklfdhjkslfhjdkslahfjkdsahjfds");
  Brain.Screen.drawRectangle (140, 20, 15, 15);
  
}

void Drive(int rspeed, int lspeed, int duration){
  LF.spin(forward, lspeed, pct);
  RF.spin(forward, rspeed, pct);
  LB.spin(forward, lspeed, pct);
  RB.spin(forward, rspeed, pct);

  wait(duration, msec);
}
void stopRobot() {
LF.stop(brake);
RF.stop(brake);
LB.stop(brake);
RB.stop(brake);
}

void inchDrive(int inches){
  float x = 0;
  float error = inches - x;
  float kp = 10.0;
  float speed = kp * error;

  LF.setPosition(0, rev);

  while (fabs(error) > 0.4) {
    Drive(speed, speed, 10);
    x = LF.position(rev)*M_PI*dia*gearRatio;
    error = inches - x;
    speed = kp *error;
  }
  stopRobot();
  Brain.Screen.printAt(100, 20, "distance=  %0.1f ", x);
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
  inchDrive(12);
  wait(100, msec);
  Drive(-10, 10, 500);
  wait(100, msec);
  Drive(10, 10, 500);
  wait(100, msec);
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
  printscreen();
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
