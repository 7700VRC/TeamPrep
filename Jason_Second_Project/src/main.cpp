/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      5/15/2025, 4:31:28 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

//Brain/Control
controller Controller1();
brain Brain;

//Drive Motors
motor RF (PORT10, ratio6_1 , false);
motor RB (PORT19, ratio6_1 , false);
motor LF (PORT11, ratio6_1 , true);
motor LB (PORT4, ratio6_1 , true);

//Gyro
inertial GYRO (PORT13);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//Function to stop robot
void Robotstop() {
RF.stop (brake);
RB.stop (brake);
LF.stop (brake);
LB.stop (brake);
}

//Function to drive robot
void Robotdrive (int Lspeed, int Rspeed, int duration) {
RF.spin (fwd, Rspeed, pct);
RB.spin (fwd, Rspeed, pct);
LF.spin (fwd, Lspeed, pct);
LB.spin (fwd, Lspeed, pct);
wait (duration, msec);
}


void turntoAngle (float targetAngle){
float error = 0;
float lastError = 0;

float Kp = 2.0;

float Ki = 0.5;
float totalError = 0;

float Kd = 0.5;
float derivitive = 0;

float speed = 0;
float currentAngle = GYRO.heading();

while (true) {
  error = targetAngle - currentAngle;
  totalError = +error;
  derivitive = error - lastError;
  speed = (Kp * error) + (Ki * totalError) + (Kd * derivitive);  
  

  if (error > 180) error = error - 360;
  if (error < -180) error = error + 360;

  Robotdrive (speed, -speed, 10);

  if (fabs(error)<1.0) break; 
  lastError = error;
}
Robotstop ();
}



void pre_auton(void) {

 while (GYRO.isCalibrating()) wait (200, msec);
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

Robotdrive (50, 50, 2000);
Robotstop ();
//turntoAngle (90);

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
