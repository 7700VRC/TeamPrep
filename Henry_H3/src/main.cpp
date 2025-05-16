/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       -------                                                   */
/*    Created:      5/32/1503, 4:26:53 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition

competition Competition;
// define your global instances of motors and other devices here
motor LF(PORT6, ratio6_1, false);
motor LB(PORT11, ratio6_1, false);
motor RF(PORT9, ratio6_1, true);
motor RB(PORT20, ratio6_1, true);
inertial thing_that_makes_turning_work(PORT10);
controller thing_that_makes_stuff_drive;
brain Brain;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
void move(int l, int r, int wt){
  LF.spin( forward, l,pct);
  LB.spin( forward, l, pct);
  RF.spin( forward, r, pct);
  RB.spin( forward, r,  pct);
  wait (wt, msec);
}
void stop(){
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}
void turn_that_works(float tar){
float err = 0;
float kp = 1.0;
float ki = 1.0;
float ter = 0;
float kd = 32.0;
float dri = 0;
float spe = 0;
float per = 0;
while(1){
  float cua = thing_that_makes_turning_work.heading();
  err = tar - cua;
  ter = +err;
  dri = err - per;
  spe = (kp*err)+(ki*ter)+(kd*dri);
  if (err > 180)err -= 360;
  if (err < -180)err += 360;
  move(spe, -spe, 10);
  if (fabs(err)<1.0)break;
  per = err;
}
stop();
}
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  while (thing_that_makes_turning_work.isCalibrating())wait (0.2, sec);
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
  turn_that_works(90);
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
