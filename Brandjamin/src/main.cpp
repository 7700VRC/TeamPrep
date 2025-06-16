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
  Brain.Screen.printAt(10,20, "Autonomous Stage");
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
  Brain.Screen.printAt(10,50,"User Control Stage");
  while (1) {
    
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis3.position(pct);

    Lspeed = Lspeed + Controller.Axis1.position(pct);  
    Rspeed = Rspeed - Controller.Axis1.position(pct);

    

    LM.spin(fwd,Lspeed,pct);
    RM.spin(fwd,Rspeed,pct);

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
