/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Kieran Paramasivum                                        */
/*    Created:      4/14/2025, 4:47:20 PM                                     */
/*    Description:  7700F practice                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
void screenPrinting (int x1, int x2, int y1, int y2) {
Brain.Screen.printAt(x1, y1, ":/ ");

Brain.Screen.printAt(x2, y2, ":)");

Brain.Screen.setPenColor(green);
Brain.Screen.setFillColor(yellow);
Brain.Screen.drawRectangle(10, 230, 5, 5);

}
/*---------------------------------------------------------------------------*/

//Part of Pre-Auton
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
  while (1) {
   

    
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  screenPrinting(242,400,135,10 ); //These numbers represent x1,x2,y1,y2 as definied in the Screen Printing section
  wait(2, sec);
  Brain.Screen.clearScreen();
  screenPrinting(42,250, 100, 50);
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
