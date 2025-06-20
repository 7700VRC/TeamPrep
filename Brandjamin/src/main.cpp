/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      6/16/2025, 1:08:42 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller;
motor LM (PORT20, ratio18_1, false);
motor RM (PORT11, ratio18_1, true);
motor IN (PORT9, ratio18_1, false);
motor belt (PORT2,ratio18_1,false);
inertial Gyro (PORT5);
double pi = 3.14;
float diameter = 4.0;
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
  Brain.Screen.printAt(20,20,"Starting");
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
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
void stopAll(){
  LM.stop();
  RM.stop();
  IN.stop();
  belt.stop();
}
void inRevDrive(double dist, int speed){
  double circ = pi*diameter;
  RM.resetPosition();
  double rotations = RM.position(rev);
  double x = circ*rotations;
  while(x>dist){
    Brain.Screen.print("Loop running");
    LM.spin(fwd, -speed, pct);
    RM.spin(fwd, -speed, pct);
    rotations = RM.position(rev);
    x = circ*rotations;
  }

  LM.stop();
  RM.stop();
  Brain.Screen.print("Stopped");
  }
void inDrive(double dist, int speed){
  double circ = pi*diameter;
  LM.resetPosition();
  double rotations = LM.position(rev);
  double x = circ*rotations;
  while(x<dist){
    Brain.Screen.print("Loop running");
    LM.spin(fwd, speed, pct);
    RM.spin(fwd, speed, pct);
    rotations = LM.position(rev);
    x = circ*rotations;
  }
Brain.Screen.clearLine();
  LM.stop();
  RM.stop();
  Brain.Screen.print("Stopped");
  }


void drive(double time,int speed){

  LM.spin(fwd,speed,pct);
  RM.spin(fwd,speed,pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}
void leftTurn(double time,int speed,int xLspeed){
  LM.spin(fwd,speed*xLspeed,pct);
  RM.spin(fwd,speed,pct);
  wait(time, sec);
  RM.stop();
  LM.stop();
}
void rightTurn(double time,int speed,int xRspeed){
  RM.spin(fwd,speed*xRspeed,pct);
  LM.spin(fwd,speed,pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}

void gyroRight(double angle){
  Gyro.resetHeading();
  double currentHeading = Gyro.rotation(degrees);
  while(angle>currentHeading){
    LM.spin(fwd, 20, pct);
    RM.spin(fwd,-20,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void gyroLeft(double angle){
  Gyro.resetRotation();
  Gyro.resetHeading();
  double currentHeading = Gyro.rotation(degrees);
  angle = -angle;
  while(angle<currentHeading){
    LM.spin(fwd,-20,pct);
    RM.spin(fwd,20,pct);
    currentHeading = Gyro.rotation(degrees);
  }
}
void gyroRight2(double angle){
  double currentHeading = Gyro.heading(degrees);
  while(angle>currentHeading){
    LM.spin(fwd, 10, pct);
    RM.spin(fwd,-10,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void gyroLeft2(double angle){
  double currentHeading = Gyro.rotation(degrees);
  angle = -angle;
  while(angle>currentHeading){
    Brain.Screen.print("Turning");
    LM.spin(fwd,-10,pct);
    RM.spin(fwd,10,pct);
    currentHeading = Gyro.rotation(degrees);
  }
  Brain.Screen.clearLine();
}
//
void centerL2(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading<currentHeading){
    LM.spin(fwd,0, pct);
    RM.spin(fwd,10,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerR2(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading>currentHeading){
    LM.spin(fwd,10, pct);
    RM.spin(fwd,0,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerRL2(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading>currentHeading){
    LM.spin(fwd,0, pct);
    RM.spin(fwd,-10,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerRR2(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading<currentHeading){
    LM.spin(fwd,10, pct);
    RM.spin(fwd,0,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
//
void centerL(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading<currentHeading){
    LM.spin(fwd,-20, pct);
    RM.spin(fwd,20,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerR(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading>currentHeading){
    LM.spin(fwd,20, pct);
    RM.spin(fwd,0,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerRL(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading>currentHeading){
    LM.spin(fwd,0, pct);
    RM.spin(fwd,-20,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void centerRR(int heading){
  double currentHeading = Gyro.heading(degrees);
  while(heading<currentHeading){
    LM.spin(fwd,-20, pct);
    RM.spin(fwd,0,pct);
    currentHeading = Gyro.rotation(degrees);
 }
}
void autonomous(void) {
  Brain.Screen.clearScreen();
  int auton = 1; 
  //Auton 1
  while(auton == 1){
  inDrive(10,85);
  gyroRight(80);
  centerL(90);
  centerR(90);
  inDrive(45,100);
  inRevDrive(-1.65,30);
  gyroRight2(170);
  centerRL(180);
  centerRR(180);
  inRevDrive(-15,50);
  belt.spin(fwd,50,pct);
  wait(5,sec);
  stopAll();
  }
  //Auton 2
  while(auton == 2){
  inDrive(10,85);
  gyroLeft(75);
  centerL2(-90);
  centerR2(-90);
  inDrive(45,100);
  inRevDrive(-1.75,30);
  gyroLeft2(170);
  centerRL2(-180);
  centerRR2(-180);
  inRevDrive(-15,50);
  belt.spin(fwd,50,pct);
  wait(5,sec);
  stopAll();
  }
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
  // User control code here, inside the loop
  stopAll();
  Brain.Screen.clearScreen();
  while (1) {
  //Motor Speed values  
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis3.position(pct);
    int IntakeSpeed = 100;


//Turning mechanism
    Lspeed = Lspeed + Controller.Axis1.position(pct);  
    Rspeed = Rspeed - Controller.Axis1.position(pct);


  
//DRIVE
    LM.spin(fwd,Lspeed,pct);
    RM.spin(fwd,Rspeed,pct);
//Intake
    if(Controller.ButtonR1.pressing()){
    IN.spin(fwd,IntakeSpeed,pct);
}
    else
      if(Controller.ButtonL1.pressing()){
      IN.spin(fwd,-IntakeSpeed,pct);
      }
    else
      IN.stop();

//Lights
if(Controller.ButtonX.pressing()){
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonY.pressing()){
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonB.pressing()){
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonA.pressing()){
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonUp.pressing()){
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonLeft.pressing()){
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(purple);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonDown.pressing()){
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(purple);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}
//Lights
if(Controller.ButtonRight.pressing()){
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(purple);
  Brain.Screen.drawRectangle(0,0,480,272);

  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(0,0,480,272);
  Brain.Screen.clearScreen();
}


//Belt
  if(Controller.ButtonR2.pressing()){
    belt.spin(fwd,75,pct);
  }
  else
  if(Controller.ButtonL2.pressing()){
    belt.spin(fwd,-75,pct);
}

else
    belt.stop();

//Functions
  //Stop All
    if(Controller.ButtonRight.pressing()){
      stopAll();
    }

  //In
    if(Controller.ButtonA.pressing()){
      IN.spin(fwd,100,pct);
      wait(1,sec);
      IN.spin(fwd,100,pct);
      wait(200,msec);
      IN.spin(fwd,100,pct);
      wait(50,msec);
      IN.spin(fwd,100,pct);
      wait(50,msec);
      IN.spin(fwd,100,pct);
      wait(50,msec);
      IN.spin(fwd,100,pct);
      wait(50,msec);
      IN.spin(fwd,100,pct);
      wait(50,msec);
      IN.spin(fwd,100,pct);
      wait(0.25,sec);
      IN.stop();
      belt.spin(fwd,50,pct);
      wait(1,sec);
      IN.stop();
      belt.stop();
    }
  //OutHigh
      if(Controller.ButtonX.pressing()){
      belt.spin(fwd,50,pct);
      wait(2,sec);
      belt.spin(fwd,-100,pct);
      belt.stop();
    }
  //OutMid
      if(Controller.ButtonY.pressing()){
      belt.spin(fwd,50,pct);
      wait(2,sec);
      belt.stop();
    }
  //OutLow
      if(Controller.ButtonB.pressing()){
      IN.spin(fwd,-100,pct);
      belt.spin(fwd,-50,pct);
      wait(2,sec);
      IN.stop();
      belt.stop();
    






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
