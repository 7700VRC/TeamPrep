/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jason Au                                                  */
/*    Created:      4/17/2025, 4:05:56 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

//Robot Used (7700A)

brain Brain;

motor LB (PORT19, ratio6_1, true);
motor LF (PORT20, ratio6_1, true);
motor RB (PORT12, ratio6_1, false);
motor RF (PORT11, ratio6_1, false);

inertial Gyro (PORT15);

//Define variables
float WD = 3.25;
float GR = 0.6;

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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  while (Gyro.isCalibrating())wait(200, msec);
}

//screen pixle extremes are 0,0 and 480,272

void draw_brain_screen () {
  Brain.Screen.printAt (240, 135, "middle");
  Brain.Screen.printAt (100, 80, "quadrent 2");
  Brain.Screen.printAt (100, 200, "quadrent 3");
  Brain.Screen.printAt (360, 80, "quadrent 1");
  Brain.Screen.printAt (360, 200, "quadrent 4");
}

int draw_shapes (){

Brain.Screen.setFillColor (yellow);
Brain.Screen.setPenColor (white);
Brain.Screen.setPenWidth (5);
Brain.Screen.drawRectangle(360, 50, 70, 70);
Brain.Screen.setFillColor (green);
Brain.Screen.setPenColor (black);
Brain.Screen.drawCircle(395, 85, 25);
  return 0;
}



//drive things


void moveRobot (int rspeed, int lspeed, int duration) {
  LF.spin (forward, lspeed, pct);
  LB.spin (forward, lspeed, pct);
  RF.spin (forward, rspeed, pct);
  RB.spin (forward, rspeed, pct);

  wait(duration, msec);
}


void stopRobot () {
  LF.stop (brake);
  LB.stop (brake);
  RF.stop (brake);
  RB.stop (brake);
}


void inchDrive (float inches){
  float x = 0;
  float error = inches - x;
  float KP = 3.0;
  float speed =  error * KP;

LF.resetPosition();
LB.resetPosition();
RF.resetPosition();
RB.resetPosition();

while (fabs (error > 0.5)){
moveRobot(speed, speed, 10);
x = LF.position(rev) * WD * M_PI * GR;
error = inches - x;
speed = error * KP;
}
stopRobot();

}

void printGyro (){
  Brain.Screen.printAt(10, 20, "Heading = %0.1f", Gyro.heading (deg));
  Brain.Screen.printAt(10, 40, "Rotation = %0.1f", Gyro.rotation (deg));
  Brain.Screen.printAt(10, 60, "Yaw = %0.1f", Gyro.yaw (deg));
  Brain.Screen.printAt(10, 80, "Roll = %0.1f", Gyro.roll (deg));
  Brain.Screen.printAt(10, 100, "Pitch = %0.1f", Gyro.pitch (deg));
}
// lebrown le brown lecrown James LeArash James
void GyroTurn (float degrees) {
 
 if (degrees > 0){

  while (Gyro.rotation (deg) < degrees){


moveRobot (-50, 50, 30);

    wait(30,msec);
    }
  

}
else if (degrees<0){
 while (Gyro.rotation (deg) < degrees){
moveRobot (50, -50, 30);

    wait(30,msec);
}}
  stopRobot();
}




void Pturn (float targetDegrees) {
  float heading = Gyro.rotation (deg);
  float error = targetDegrees - heading;
  float Kp = 1.0;
  float speed = Kp * error;

  while (fabs (error) > 5){
    moveRobot (-50, 50, 30);
    wait (30, msec);

    heading = Gyro.rotation (deg);
    error = heading -targetDegrees;
    speed = error * Kp;

  }
  stopRobot();
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

  Pturn (90);
wait (1, sec);
Pturn (-90);
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
    // .......................................................................
    printGyro ();
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




