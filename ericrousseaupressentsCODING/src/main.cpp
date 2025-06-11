/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      4/17/2025, 4:08:42 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor LF(PORT2, ratio18_1, false);
motor LB(PORT19, ratio18_1, false) ;
motor RF(PORT5, ratio18_1, true);
motor RB(PORT11, ratio18_1, true);
inertial thingy (PORT3);
motor intake(PORT8, ratio18_1, true);
// define your global instances of motors and other devices here
brain Brain;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */

//return type: int, float, void

  int drawshapes ()
  {

Brain.Screen.setPenColor(blue);
Brain.Screen.setFillColor(yellow);
Brain.Screen.drawRectangle(240, 135, 20, 20);
return 0;

  }

  void printgyro() {
    Brain.Screen.printAt(10, 20,"Heading= %0.1f", thingy.heading(deg));
    Brain.Screen.printAt(10, 40,"Rotation= %0.1f", thingy.rotation(deg));
    Brain.Screen.printAt(10, 60,"Yaw= %0.1f", thingy.yaw(deg));
    Brain.Screen.printAt(10, 80,"Roll= %0.1f", thingy.roll(deg));
    Brain.Screen.printAt(10, 20,"pitch= %0.1f", thingy.pitch(deg));
  }
/*---------------------------------------------------------------------------*/

// void gyroturn(float degrees){

//   while(thingy.rotation(deg)< degrees){

//     RF.spin(forward, -speed. pct);
//     RB.spin(forward, -speed. pct);
//     LF.spin(forward, speed. pct);
//     LB.spin(forward, speed. pct);
//     wait(30, msec);
   
//     heading = thingy.rotation(deg);
//     error = heading - targetdegrees;
//     speed = error * kp;
//     //moverobot(-50, 50, 30);
//   }
// LF.stop(brake);
// LB.stop(brake);
// RF.stop(brake);
// RB.stop(brake);
// }

void driveRobotI(int rspeed, int lspeed, int wt) { 
    RF.spin(forward, rspeed. pct);
    RB.spin(forward, rspeed. pct);
    LF.spin(forward, lspeed. pct);
    LB.spin(forward, lspeed. pct);
    wait(wt, msec); 
}


void Pturn(float targetdegrees) {
  float heading = thingy.rotation(deg);
  float error = heading - targetdegrees;
  float kp = 0.5; // constant P gain
  float speed = kp * error;
while(fabs (error)> 5){

    RF.spin(forward, speed, pct);
    RB.spin(forward, speed, pct);
    LF.spin(forward, -speed, pct);
    LB.spin(forward, -speed, pct);
    wait(30, msec);
   
    heading = thingy.rotation(deg);
    error = heading - targetdegrees;
    speed = error * kp;
    //moverobot(-50, 50, 30);
  }
LF.stop(brake);
LB.stop(brake);
RF.stop(brake);
RB.stop(brake);
}













void pre_auton(void) {

  while(thingy.isCalibrating())wait(200, msec);
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
  Pturn(90);
  wait(1, sec);
  Pturn(-90);
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
