/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/17/2025, 4:34:17 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
brain Brain;
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drawOnScreen () {

Brain.Screen.print("The champions have risen");
Brain.Screen.printAt(60, 68, "Henry is King!!!!");
Brain.Screen.printAt(300, 68,  "Henry is King!!!!");
Brain.Screen.printAt(60, 203,  "Henry is King!!!!");
Brain.Screen.printAt(300, 203,  "Henry is King!!!!");
Brain.Screen.printAt(160, 135,  "Tianrui has fallen!!!!");

}
int drawShape(){
  Brain.Screen.setPenWidth(20);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(50, 50, 50, 50);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setPenWidth(7);
  Brain.Screen.drawCircle(79, 79, 15);
  return 0;
}
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
  
    drawOnScreen();
    wait(100, msec);
    Brain.Screen.clearScreen();
    drawShape();
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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
