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
motor IN (PORT9, ratio36_1, false);
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
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(50,50,30,200);
  Brain.Screen.drawRectangle(80,210,150,30);
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
void drive(double time,int speed){

  LM.spin(fwd,speed,pct);
  RM.spin(fwd,speed,pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}
void leftTurn(double time,int speed){

  RM.spin(fwd,speed,pct);
  wait(time, sec);
  RM.stop();

}
void rightOrbit(double time,int speed){
  RM.spin(fwd,speed*0.6,pct);
  LM.spin(fwd,speed,pct);
  wait(time, sec);
  LM.stop();
  RM.stop();

}
void autonomous(void) {
  
  drive(1,50);
  leftTurn(1.25,50);
  drive(0.75,50);
  rightOrbit(7.5,50);
  leftTurn(1.15,50);
  drive(1,50);
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
 
  while (1) {
  //Motor Speed values  
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis3.position(pct);
    int IntakeSpeed = 100;
//L2, R2
int Speed2;
if(Controller.ButtonR2.pressing()){
  Speed2 = 100;
}
else
if(Controller.ButtonL2.pressing()){
  Speed2 = -100;
  }
  else{
  Speed2 = 0;
}
    Lspeed = Lspeed + Speed2;
    Rspeed = Rspeed + Speed2;

//Turning mechanism
    Lspeed = Lspeed + Controller.Axis4.position(pct);  
    Rspeed = Rspeed - Controller.Axis4.position(pct);


  
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

