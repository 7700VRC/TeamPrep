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
// RMmotor              motor         18              
// LMmotor              motor         19              
// RFmotor              motor         17              
// LBmotor              motor         16              
// RBmotor              motor         15              
// LFmotor              motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
float D=4.0;
float G=1.0;
float Pi=3.14159;

int AutonSelected=0;
int AutonMin=0;
int AutonMax=4;

void drawGUI(){
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Auton and then press Go..... Also have you ever wondered waht the meaning of life is?");
  Brain.Screen.printAt(1, 200, "Auton selected=%d  ", AutonSelected);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.drawCircle(300, 75, 25);
  Brain.Screen.printAt(25, 75 , "select");



Brain.Screen.setFillColor(black);
}

void selectAuton() {
  bool selectingAuton = true;

  int x = Brain.Screen.xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen.yPosition(); // get the y position of last touch of the screen
  // check to see if buttons were pressed
  if (x >= 20 && x <= 120 && y >= 50 && y <= 150) // select button pressed
  {
    AutonSelected++;
    if (AutonSelected > AutonMax)AutonSelected = AutonMin; // rollover
      
    Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonSelected);
  }
  if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
    selectingAuton = false; // GO button pressed
    Brain.Screen.printAt(1, 200, "Auton  =  %d   GO           ", AutonSelected);
  }
  if (!selectingAuton) {
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawCircle(300, 75, 25);
  } else {
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawCircle(300, 75, 25);
  }
  wait(10, msec); // slow it down
  Brain.Screen.setFillColor(black);
}




void drive(int lspeed, int rspeed, int wt){
  LMmotor.spin(forward, lspeed, pct);
  LFmotor.spin(forward, lspeed, pct);
  LBmotor.spin(forward, lspeed, pct);
  RMmotor.spin(forward, rspeed, pct);
  RFmotor.spin(forward, rspeed, pct);
  RBmotor.spin(forward, rspeed, pct);
  wait(wt, msec);
}
void driveBrake(){
LMmotor.stop(brake);
LFmotor.stop(brake);
LBmotor.stop(brake);
RMmotor.stop(brake);
RFmotor.stop(brake);
RBmotor.stop(brake);
}






void inchDrive(float target, float speed=50) {
  float accuracy=0.2;
  float x=0.0;
  float error=target-x;

  LMmotor.setRotation(0, rev);
  while(fabs(error)>accuracy){
    speed=fabs(speed)*fabs(error)/error;
    drive(speed, speed, 10);
    x=G*LMmotor.rotation(rev)*Pi*D;
    error=target-x;
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
  drawGUI();
  Brain.Screen.pressed(selectAuton);
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

switch (AutonSelected) {
  case 0:
 wait (1000, msec);
  break;
    case 1:
  inchDrive(24);
wait(1, seconds);
inchDrive(-24);
  break;
    case 2:
   inchDrive(48);
wait(1, seconds);
inchDrive(-24);
  break;
    case 3:
  //code 3
  break;
    case 4:
  //code 4
  break;
  }


inchDrive(24);
wait(1, seconds);
inchDrive(-24);


/*
drive(50, 50, 800);
driveBrake();
drive(50, -50, 500);
driveBrake();
drive(50, 50, 1000);
driveBrake();
drive(-50, 50, 500);
driveBrake();
drive(50, 50, 800);
driveBrake();
drive(30, -30, 500);
driveBrake();
drive (50, 50, 800);
driveBrake();
drive(50, 50, 3000);
driveBrake();
*/

Brain.Screen.printAt(1, 20, "never gonna give you up never gonna let you down");
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
    int lstick=Controller1.Axis3.position(pct);
    int rstick=Controller1.Axis2.position(pct);
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
//where did they all go? all of them?