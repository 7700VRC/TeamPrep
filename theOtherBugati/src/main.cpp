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
// LeftMotor            motor         1               
// RightMotor           motor         10              
// Roller               motor         2               
// Color                optical       3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
float D = 4.0; //Wheel diameter
float G = 1.0; //Outside gear ratio
float Pi = 3.14; 
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt){
LeftMotor.spin(forward, lspeed, pct);
RightMotor.spin(forward, rspeed, pct);
wait(wt, msec);
}

void DriveBrake(){
LeftMotor.stop(brake);
RightMotor.stop(brake);
}

void InchDrive(float target, float speed = 50){
LeftMotor.setRotation(0, rev);
float x = 0;
float error = target - x;
float accuracy =  0.2;
while(fabs(error) > accuracy){
drive(speed, speed, 10);
x = LeftMotor.rotation(rev)*Pi*D*G;
error=target-x;
}
DriveBrake();
}
//Borange Bugatti fire
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
wait(500, msec);
InchDrive(24);
drive(50, -50, 660);
InchDrive(24);
drive(50, -50, 660);
InchDrive(24);
drive(50, -50, 660);
InchDrive(24);
drive(50, -50, 660);
DriveBrake();
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
  while (true) {
  
    int lstick=Controller1.Axis3.position();
    int rstick=Controller1.Axis2.position();
    drive(lstick, rstick, 10);

    if(Controller1.ButtonR1.pressing()){
      Roller.spin(forward, 70, pct);
    }
  else if(Controller1.ButtonR2.pressing()){
    Roller.spin(forward, -70, pct);
  }
  else{
    Roller.spin(forward, 0, pct);
  }
  }
}
// What is the chromatic shade of your quad wheeled back wheel drive auto transmission bugatti bra
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
