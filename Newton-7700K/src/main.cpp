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
// RM                   motor         18              
// LM                   motor         19              
// RF                   motor         17              
// LB                   motor         16              
// RB                   motor         15              
// LF                   motor         2               
// Intake               motor         13              
// Gyro                 inertial      12              
// Color                optical       1               
// Dist                 distance      5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

float pi = 3.1415926535897932387629433;
float D = 4.0;
float G = 3.0/5.0;
float Diagonal = 33.941;
int AutonSelected;
int AutonMin = 0;
int AutonMax = 3;
int Color1 = 0;

void drawGUI(){
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Auton");
  Brain.Screen.printAt(1, 200, "Auton selected: %d ", AutonSelected);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.drawCircle(300, 75, 25);
  Brain.Screen.printAt(25, 75, "Select");
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(170, 50, 100, 100);
  Brain.Screen.printAt(175, 75, "GO");
  Brain.Screen.setFillColor(black);
}
void selectAuton() {
  bool selectingAuton = true;

  int x = Brain.Screen.xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen.yPosition(); // get the y position of last touch of the screen
  // check to see if buttons were pressed
  if (x >= 20 && x <= 120 && y >= 50 && y <= 150) // select button pressed
  {
    AutonSelected = AutonSelected + 1;
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
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
void drive(int Lspeed, int Rspeed, int wt){
  LF.spin(forward, Lspeed, pct);
  LM.spin(forward, Lspeed, pct);
  LB.spin(forward, Lspeed, pct);
  RF.spin(forward, Rspeed, pct);
  RM.spin(forward, Rspeed, pct);
  RB.spin(forward, Rspeed, pct);
  wait(wt, msec);
}
void driveBrake(){
  LF.stop(brake);
  RF.stop(brake);
  LM.stop(brake);
  RM.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}

void inchDrive(float target, float speed = 50){
  float accuracy = 0.2;
  float x = 0.0;
  float error = target-x;

  LM.setRotation(0, rev);
  while(fabs(error) > accuracy){
    speed = fabs(speed) * fabs(error)/error;
    drive(speed, speed, 10);
    x = G * LM.rotation(rev)*pi*D;
    error = target - x;
  }
  driveBrake();
}

void gyroTurn(float target){
  Gyro.setRotation(0.0, deg);
  float heading = 0.0;
  float error = target - heading;
  float accuracy = 1.0;
  float speed = 50;
  float kp = 0.25;
  float b=5.0;
  while(fabs(error)>accuracy)
  {
    speed = kp * error+b*fabs(error)/error;
    drive(speed, -speed, 10);
    heading = Gyro.rotation(deg);
    error = target - heading;
    Brain.Screen.printAt(1, 160, "heading = %.2f  deg", heading);
  }
  driveBrake();
}
void getColor(){
  Color.setLightPower(50);
  Color1 = Color.value();
  Brain.Screen.printAt(1, 200, "Color   %d    ",Color1);

  //red is 19-35
  //blue is 170-220

}
void getDistance(){
  int x = Dist.objectDistance(inches);
  Brain.Screen.printAt(1, 220, "Distance   %d    ",x);
}
void spinIntake(int sp, int wt = 0){
  Intake.spin(forward, sp, pct);
  wait(wt, msec);
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

void pre_auton() {
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
    drive(-10, -10, 120);
    while(Color1 >= 0 && Color1 <= 100){
      getColor();
      spinIntake(-90, 10);
      Brain.Screen.printAt(1, 240, "Color   %d    ",Color1);
    }
    spinIntake(0);
    inchDrive(20);
    gyroTurn(40);
    driveBrake();
    inchDrive(150);
    gyroTurn(-130);
    inchDrive(-40);
    while(Color1 >= 19 && Color1 <= 35){
      spinIntake(-90);
    }

  break;
  case 1:
   inchDrive(38);
  gyroTurn(45);
  driveBrake();
  inchDrive(150);
  gyroTurn(-130);
  inchDrive(-40);
  
  break;
  case 2:
    drive(50, -50, 1000);
    driveBrake();
  break;
  case 3:
    drive(-50, 50, 1000);
    driveBrake();
  break;
  }
  /*
  drive(50, -50, 485);
  driveBrake();
  inchDrive(6*Diagonal);
  drive(50, -50, 20);
  driveBrake();
  inchDrive(5*Diagonal);
  drive(50, -50, 1400);
  driveBrake();
  inchDrive(-40);
  driveBrake();
  */
  /*
  drive(75, 75, 200);
  driveBrake();
  drive(50, -50, 425);
  driveBrake();
  drive(75, 75, 6000);
  driveBrake();
  Brain.Screen.printAt(1, 20, "Auton Finished");
  */
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

void driver(void) {
  // User control code here, inside the loop
  while (true) {
    float lstick=.75*Controller1.Axis3.position(pct);
    float rstick=.75*Controller1.Axis2.position(pct);
    drive(lstick, rstick, 10);
    if(Controller1.ButtonR1.pressing()){
      spinIntake(90);
    }
    else if(Controller1.ButtonR2.pressing()){
      spinIntake(-90);
    }
    else{
      spinIntake(0);
    }
    getColor();
    getDistance();
  }
}




//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(driver);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
