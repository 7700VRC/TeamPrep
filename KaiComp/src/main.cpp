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
// LeftBack             motor         7               
// RightBack            motor         6               
// Gyro                 inertial      2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;

float D=4.0; //Wheel diameter
float G=7.0/5.0; //Gear ratio
float Pi=3.14;

void drive(int lspeed,int rspeed,int wt){
  LeftFront.spin(forward, lspeed, pct);
  RightFront.spin(forward, rspeed, pct);
  LeftBack.spin(forward, lspeed, pct);
  RightBack.spin(forward, rspeed, pct);
  wait(wt, msec);
}
void driveBrake(){
  LeftFront.stop(brake);
  RightFront.stop(brake);
  LeftBack.stop(brake);
  RightBack.stop(brake);
}
void drivecoast(){
  LeftFront.stop(coast);
  RightFront.stop(coast);
  LeftBack.stop(coast);
  RightBack.stop(coast);
}

void inchDrive(float target){
  float xl=0.0;
  float xr=0.0;
  float error=target-xl;
  float accuracy=0.2;
  float kp=5.0;
  float ks=0.0;
  float speed=kp*error;
  float steer=xr-xl;
  float lspeed=kp*error+steer;
  float rspeed=kp*error-steer;

  LeftFront.setRotation(0, rev);
  RightFront.setRotation(0, rev);
  while(fabs(error)>accuracy){
    steer=ks*(xr-xl);
    speed=kp*error;

    speed=std::min(speed,float(70));
    speed=std::max(speed,float(-70));

    lspeed=speed+(ks*steer);
    rspeed=speed-(ks*steer);
    drive(lspeed,rspeed,10);

    xl=LeftFront.rotation(rev)*Pi*D*G;
    xr=RightFront.rotation(rev)*Pi*D*D;
    error=target-xl;
  }
  driveBrake();
}
void gyroTurn(float target){
  Gyro.setRotation(0.0, degrees);
  float heading=0.0;
  float error=target-heading;
  float oldError=error;
  float accuracy=2.0;
  float kp=1;
  float kd=0.1;
  
  while(fabs(error)> accuracy){
    drive(kp*error+kd*(error-oldError), -(kp*error+kd*(error-oldError)), 10);
    heading=Gyro.rotation(degrees);
    oldError=error;
    error=target-heading;
    std::cout<<heading<<std::endl;
  }
  driveBrake();
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

/*---------------------------------------------------------------------------*/
/*                            Autonomous Functions                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  inchDrive(52);
  wait(100, msec);
  gyroTurn(90);
  wait(100, msec);
  inchDrive(100);
  wait(100, msec);

}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*                                                                           */
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
