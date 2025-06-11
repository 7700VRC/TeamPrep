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
// LeftFront            motor         4               
// RightFront           motor         5               
// RightBack            motor         6               
// LeftBack             motor         7               
// Gyro                 inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
float D = 4.0;       // wheel diameter inches
float G = 7.0 / 5.0; // gear ratio
float Pi = 3.14;

void drive(int lspeed, int rspeed, int wt) {
  LeftFront.spin(forward, lspeed, pct);
  RightFront.spin(forward, rspeed, pct);
  LeftBack.spin(forward, lspeed, pct);
  RightBack.spin(forward, rspeed, pct);
  wait(wt, msec);
}

void driveBrake() {
  LeftFront.stop(brake);
  RightFront.stop(brake);
  LeftBack.stop(brake);
  RightBack.stop(brake);
}

void drivecoast() {
  LeftFront.stop(coast);
  RightFront.stop(coast);
  LeftBack.stop(coast);
  RightBack.stop(coast);
}

void inchDrive(float target) {
  float xl = 0.0;
  float xr = 0.0;
  float error = target - xl;
  float accuracy = 0.2;
  float steer = xr - xl;
  float kp = 5.0;
  float ks = 1.0;
  float speed = kp * error;
  float lspeed = kp * error + steer;
  float rspeed = kp * error - steer;
  LeftFront.setRotation(0, rev);
  RightFront.setRotation(0, rev);
  while (fabs(error) > accuracy) {
    steer = ks * (xr - xl);
    speed = kp * error;

    speed = std::min(speed, float(100.0));
    speed = std::max(speed, float(-100.0));

    lspeed = speed + steer;
    rspeed = speed - steer;
    drive(lspeed, rspeed, 10);

    xl = LeftFront.rotation(rev) * Pi * D * G;
    xr = RightFront.rotation(rev) * Pi * D * G;
    error = target - xl;
  }
  driveBrake();
}

void gyroTurn(float target){
  Gyro.setRotation(0.0, degrees);
  float heading=0.0;
  float error=target-heading;
  float accuracy=2.0;
  float kp=1.0;
  while(true){
    drive(kp*error, -kp*error, 10);
    heading=Gyro.rotation(degrees);
    error=target-heading;
    std::cout<<heading<<std::endl;
}
  driveBrake();

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
  inchDrive(24);
  wait(1000, msec);
  inchDrive(-24);
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
  int lstick = 0;
  int rstick = 0;
  while (true) {
    lstick = Controller1.Axis3.position();
    rstick = Controller1.Axis2.position();

    drive(lstick, rstick, 10);
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
